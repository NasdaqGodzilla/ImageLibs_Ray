// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2014.
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
#include "egl3_texture.h"

_NAME_BEGIN

__ImplementSubClass(EGL3Texture, GraphicsTexture, "EGL3Texture")

EGL3Texture::EGL3Texture() noexcept
	: _texture(0)
	, _target(GL_NONE)
{
}

EGL3Texture::~EGL3Texture() noexcept
{
	this->close();
}

bool
EGL3Texture::setup(const GraphicsTextureDesc& textureDesc) noexcept
{
	assert(_texture == GL_NONE);

	GLenum target = EGL3Types::asTextureTarget(textureDesc.getTexDim(), textureDesc.isMultiSample());
	if (target == GL_INVALID_ENUM)
		return false;

	GL_CHECK(glGenTextures(1, &_texture));
	if (_texture == GL_NONE)
	{
		GL_PLATFORM_LOG("glGenTextures fail");
		return false;
	}

	GL_CHECK(glBindTexture(target, _texture));

	GLsizei w = (GLsizei)textureDesc.getWidth();
	GLsizei h = (GLsizei)textureDesc.getHeight();
	GLsizei depth = (GLsizei)textureDesc.getDepth();

	if (!applySamplerWrap(target, textureDesc.getSamplerWrap()))
		return false;

	if (!applySamplerFilter(target, textureDesc.getSamplerFilter()))
		return false;

	if (!applySamplerAnis(target, textureDesc.getSamplerAnis()))
		return false;

	auto internalFormat = EGL3Types::asTextureInternalFormat(textureDesc.getTexFormat());
	if (internalFormat == GL_INVALID_ENUM)
		return false;

	GLsizei level = target == GL_TEXTURE_CUBE_MAP ? 6 : 1;
	level = std::max(level, textureDesc.getMipLevel());

	if (target == GL_TEXTURE_2D)
		GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, level, internalFormat, w, h));
	else if (target == GL_TEXTURE_2D_MULTISAMPLE)
		GL_CHECK(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, level, internalFormat, w, h, GL_FALSE));
	else if (target == GL_TEXTURE_2D_ARRAY)
		GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, level, internalFormat, w, h, depth));
	else if (target == GL_TEXTURE_3D)
		GL_CHECK(glTexStorage3D(GL_TEXTURE_3D, level, internalFormat, w, h, depth));
	else if (target == GL_TEXTURE_CUBE_MAP)
		GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP, level, internalFormat, w, h));

	auto stream = textureDesc.getStream();
	if (stream)
	{
		if (EGL3Types::isCompressedTexture(textureDesc.getTexFormat()))
		{
			GLsizei size = textureDesc.getMipSize();
			std::size_t offset = 0;
			std::size_t blockSize = internalFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16;

			for (GLint mip = 0; mip < level; mip++)
			{
				auto mipSize = ((w + 3) / 4) * ((h + 3) / 4) * blockSize;

				GL_CHECK(glCompressedTexSubImage2D(GL_TEXTURE_2D, mip, 0, 0, w, h, internalFormat, mipSize, (char*)stream + offset));

				w = std::max(w >> 1, 1);
				h = std::max(h >> 1, 1);

				offset += mipSize;
			}
		}
		else
		{
			auto format = EGL3Types::asTextureFormat(textureDesc.getTexFormat());
			auto type = EGL3Types::asTextureType(textureDesc.getTexFormat());

			switch (target)
			{
			case GL_TEXTURE_2D:
				GL_CHECK(glTexSubImage2D(target, 0, 0, 0, w, h, format, type, stream));
				break;
			case GL_TEXTURE_2D_ARRAY:
				GL_CHECK(glTexSubImage3D(target, 0, 0, 0, 0, w, h, depth, format, type, stream));
				break;
			case GL_TEXTURE_3D:
				GL_CHECK(glTexSubImage3D(target, 0, 0, 0, 0, w, h, depth, format, type, stream));
				break;
			case GL_TEXTURE_CUBE_MAP:
				GL_CHECK(glTexSubImage3D(target, 0, 0, 0, 0, w, h, 6, format, type, stream));
				break;
				break;
			default:
				assert(false);
				break;
			}
		}
	}

	_target = target;
	_textureDesc = textureDesc;

	if (textureDesc.isMipmap())
		GL_CHECK(glGenerateMipmap(target));

	return EGL3Check::checkError();
}

void
EGL3Texture::close() noexcept
{
	if (_texture)
	{
		glDeleteTextures(1, &_texture);
		_texture = GL_NONE;
	}
}

GLenum
EGL3Texture::getTarget() const noexcept
{
	return _target;
}

GLuint
EGL3Texture::getInstanceID() const noexcept
{
	return _texture;
}

bool
EGL3Texture::applySamplerWrap(GLenum target, GraphicsSamplerWrap wrap) noexcept
{
	GLenum glwrap = EGL3Types::asSamplerWrap(wrap);
	if (glwrap != GL_INVALID_ENUM)
	{
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_S, glwrap));
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_T, glwrap));
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_R, glwrap));

		return true;
	}

	return false;
}

bool
EGL3Texture::applySamplerFilter(GLenum target, GraphicsSamplerFilter filter) noexcept
{
	GLenum glfilter = EGL3Types::asSamplerFilter(filter);
	if (glfilter != GL_INVALID_ENUM)
	{
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, glfilter));
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, glfilter));

		return true;
	}

	return false;
}

bool
EGL3Texture::applySamplerAnis(GLenum target, GraphicsSamplerAnis anis) noexcept
{
	if (anis == GraphicsSamplerAnis::GraphicsSamplerAnis1)
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1));
	else if (anis == GraphicsSamplerAnis::GraphicsSamplerAnis2)
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2));
	else if (anis == GraphicsSamplerAnis::GraphicsSamplerAnis4)
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4));
	else if (anis == GraphicsSamplerAnis::GraphicsSamplerAnis8)
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8));
	else if (anis == GraphicsSamplerAnis::GraphicsSamplerAnis16)
		GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16));
	else
	{
		if (anis != GraphicsSamplerAnis::GraphicsSamplerAnis0)
		{
			GL_PLATFORM_LOG("Can't support anisotropy format");
			return false;
		}
	}

	return true;
}

const GraphicsTextureDesc&
EGL3Texture::getGraphicsTextureDesc() const noexcept
{
	return _textureDesc;
}

void
EGL3Texture::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
EGL3Texture::getDevice() noexcept
{
	return _device.lock();
}

_NAME_END