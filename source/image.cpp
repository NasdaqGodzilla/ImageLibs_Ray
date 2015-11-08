// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include <ray/image.h>
#include <ray/imagall.h>

_NAME_BEGIN

Image::Image() noexcept
{
	this->_init();
}

Image::Image(istream& stream, image_type type) noexcept
{
	this->_init();
    this->load(stream, type);
}

Image::Image(size_type width, size_type height, bpp_type bpp, bool clear) noexcept
{
	this->_init();
    this->create(width, height, bpp, clear);
}

Image::Image(size_type width, size_type height, bpp_type bpp, std::size_t dataSize, image_buf data, bool staticData, bool clear) noexcept
{
	this->_init();
    this->create(width, height, bpp, dataSize, data, staticData, clear);
}

Image::~Image() noexcept
{
    this->destroy();
}

bool
Image::create(size_type width, size_type height, bpp_type bpp, bool clear) noexcept
{
	std::size_t destLength = (width * height * bpp) >> 3;

	this->destroy();

	_width = width;
	_height = height;
	_bpp = bpp;
	_size = destLength;
	_isStatic = false;
	_data = new pass_val[destLength];

	this->setImageType(Image::unknown);

	if (clear) this->clear();

	return true;
}

bool
Image::create(size_type width, size_type height, bpp_type bpp, std::size_t dataSize, image_buf data, bool staticData, bool clear) noexcept
{
	assert(data);

    this->destroy();

	_width = width;
	_height = height;
	_bpp = bpp;
	_data = data;
	_size = dataSize;
	_isStatic = staticData;

	this->setImageType(Image::unknown);

	if (clear) this->clear();

	return true;
}

bool
Image::create(const Image& copy) noexcept
{
    return this->create(copy.width(), copy.height(), copy.bpp(), false);
}

void 
Image::_init() noexcept
{
	_data = nullptr;
	_mipLevel = 0;
}

void
Image::destroy() noexcept
{
    if (_data && !_isStatic)
    {
		delete[] _data;
        _data = nullptr;
    }
}

void
Image::setImageType(image_type type) noexcept
{
	_imageType = type;
}

Image::image_type
Image::getImageType() const noexcept
{
	return _imageType;
}

void 
Image::setMipLevel(std::uint8_t level) noexcept
{
	_mipLevel = level;
}

std::uint8_t 
Image::getMipLevel() const noexcept
{
	return _mipLevel;
}

Image::delay_type
Image::getFrameDelay() const noexcept
{
    return 0;
}

void
Image::setFrameDelay(delay_type /*delay*/) const noexcept
{
}

void
Image::setPalette(PaletteData* pal) noexcept
{
    assert(pal);
}

bool
Image::load(istream& stream, image_type type) noexcept
{
    if (emptyHandler())
        GetImageInstanceList(*this);

    _Myhandler impl;

	this->setImageType(type);

    if (this->find(stream, type, impl))
    {
        if (impl->doLoad(*this, stream))
        {
            return true;
        }

        this->error(impl->error());
    }
    else
    {
        this->error(image_error::NO_SUITABLE_READER);
    }

    return false;
}

bool
Image::save(ostream& stream, image_type type) noexcept
{
    if (stream.good())
    {
        _Myhandler impl;
        if (this->find(type, impl))
        {
            if (!impl->doSave(*this, stream))
            {
                this->error(impl->error());
                return false;
            }

            return true;
        }
        else
        {
            this->error(image_error::NO_SUITABLE_READER);
            return false;
        }
    }

    return false;
}

bool
Image::emptyHandler() const noexcept
{
    return this->_handlers.empty();
}

bool
Image::add(_Myhandler handler) noexcept
{
    if (nullptr == handler)
        return false;

    for (auto it : _handlers)
    {
        if (it == handler)
        {
            this->error(image_error::FILE_EXTENSION_IS_ALREADY_IN_USE);
            return false;
        }
    }

    _handlers.push_back(handler);

    return true;
}

bool
Image::remove(_Myhandler handler) noexcept
{
    if (nullptr == handler)
        return false;

    auto it = std::find(_handlers.begin(), _handlers.end(), handler);

    if (it != _handlers.end())
    {
        if (*it == handler)
        {
            _handlers.erase(it);
            return true;
        }
    }

    this->error(image_error::UNREGISTERING_CUSTOM_IMPORTER);
    return false;
}

bool
Image::find(istream& stream, _Myhandler& out) const noexcept
{
    if (stream.is_open())
    {
        for (auto it : _handlers)
        {
            stream.seekg(0, std::ios_base::beg);

            if (it->doCanRead(stream))
            {
                stream.seekg(0, std::ios_base::beg);

                out = it;
                return true;
            }
        }
    }

    return false;
}

bool
Image::find(image_type type, _Myhandler& out) const noexcept
{
    std::size_t index = (std::size_t)type;
    if (_handlers.size() < index)
    {
        out = _handlers[index];
        return true;
    }

    return false;
}

bool
Image::find(istream& stream, image_type type, _Myhandler& out) const noexcept
{
    if (type != Image::unknown)
    {
        if (this->find(type, out))
        {
            return true;
        }
    }

    return this->find(stream, out);
}

void
Image::cmyk_to_rgb(image_buf rgb, const image_buf cmyk) noexcept
{
    register int k = 255 - cmyk[3];
    register int k2 = cmyk[3];
    register int c;

    c = k + k2 * (255 - cmyk[0]) / 255;
    rgb[0] = (pass_val)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[1]) / 255;
    rgb[1] = (pass_val)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[2]) / 255;
    rgb[2] = (pass_val)((c > 255) ? 0 : (255 - c));
}

void
Image::cmyk_to_rgba(image_buf rgba, const image_buf cmyk) noexcept
{
    register int k = 255 - cmyk[3];
    register int k2 = cmyk[3];
    register int c;

    c = k + k2 * (255 - cmyk[0]) / 255;
    rgba[0] = (pass_val)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[1]) / 255;
    rgba[1] = (pass_val)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[2]) / 255;
    rgba[2] = (pass_val)((c > 255) ? 0 : (255 - c));

    rgba[3] = 255;
}

void
Image::cmyk_to_rgb(RGB* texel, const image_buf cmyk) noexcept
{
    register int k = 255 - cmyk[3];
    register int k2 = cmyk[3];
    register int c;

    c = k + k2 * (255 - cmyk[0]) / 255;
    texel->r = (unsigned char)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[1]) / 255;
    texel->g = (unsigned char)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[2]) / 255;
    texel->b = (unsigned char)((c > 255) ? 0 : (255 - c));
}

void
Image::cmyk_to_rgba(RGBA* texel, const image_buf cmyk) noexcept
{
    register int k = 255 - cmyk[3];
    register int k2 = cmyk[3];
    register int c;

    c = k + k2 * (255 - cmyk[0]) / 255;
    texel->r = (unsigned char)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[1]) / 255;
    texel->g = (unsigned char)((c > 255) ? 0 : (255 - c));

    c = k + k2 * (255 - cmyk[2]) / 255;
    texel->b = (unsigned char)((c > 255) ? 0 : (255 - c));

    texel->a = 255;
}

void
Image::hsv_to_rgb(RGB& rgb, float h, float s, float v) noexcept
{
    int i;
    float f;
    float p, q, t;

    h *= 5;

    i = (int)floor(h);
    f = h - i;

    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i)
    {
    case 0:
        rgb.r = (unsigned char)(255 * v);
        rgb.g = (unsigned char)(255 * t);
        rgb.b = (unsigned char)(255 * p);
        break;
    case 1:
        rgb.r = (unsigned char)(255 * q);
        rgb.g = (unsigned char)(255 * v);
        rgb.b = (unsigned char)(255 * p);
        break;
    case 2:
        rgb.r = (unsigned char)(255 * p);
        rgb.g = (unsigned char)(255 * v);
        rgb.b = (unsigned char)(255 * t);
        break;
    case 3:
        rgb.r = (unsigned char)(255 * p);
        rgb.g = (unsigned char)(255 * q);
        rgb.b = (unsigned char)(255 * v);
        break;
    case 4:
        rgb.r = (unsigned char)(255 * t);
        rgb.g = (unsigned char)(255 * p);
        rgb.b = (unsigned char)(255 * v);
        break;
    case 5:
        rgb.r = (unsigned char)(255 * v);
        rgb.g = (unsigned char)(255 * p);
        rgb.b = (unsigned char)(255 * q);
        break;
    }
}

void
Image::hsv_to_rgba(RGBA& rgb, float h, float s, float v) noexcept
{
    float f;
    float p, q, t;

    h *= 5;

    int i = (int)floor(h);
    f = h - i;

    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i)
    {
    case 0:
        rgb.r = (unsigned char)(255 * v);
        rgb.g = (unsigned char)(255 * t);
        rgb.b = (unsigned char)(255 * p);
        break;
    case 1:
        rgb.r = (unsigned char)(255 * q);
        rgb.g = (unsigned char)(255 * v);
        rgb.b = (unsigned char)(255 * p);
        break;
    case 2:
        rgb.r = (unsigned char)(255 * p);
        rgb.g = (unsigned char)(255 * v);
        rgb.b = (unsigned char)(255 * t);
        break;
    case 3:
        rgb.r = (unsigned char)(255 * p);
        rgb.g = (unsigned char)(255 * q);
        rgb.b = (unsigned char)(255 * v);
        break;
    case 4:
        rgb.r = (unsigned char)(255 * t);
        rgb.g = (unsigned char)(255 * p);
        rgb.b = (unsigned char)(255 * v);
        break;
    case 5:
        rgb.r = (unsigned char)(255 * v);
        rgb.g = (unsigned char)(255 * p);
        rgb.b = (unsigned char)(255 * q);
        break;
    }

    rgb.a = 255;
}

void
Image::flipImageVertical(char* data, std::size_t width, std::size_t height, std::size_t component) noexcept
{
    std::size_t size = width * height * component;
    std::size_t stride = sizeof(char)* width * component;

    char* _data = new char[sizeof(char)* size];

    for (std::size_t i = 0; i < height; i++)
    {
        std::size_t j = height - i - 1;
        memcpy(_data + j * stride, data + i * stride, stride);
    }

    memcpy(data, _data, size);

    delete[] _data;
}

_NAME_END