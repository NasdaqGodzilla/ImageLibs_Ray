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
#include <ray/render_buffer.h>

_NAME_BEGIN

RenderIndirect::RenderIndirect() noexcept
	: startVertice(0)
	, numVertices(0)
	, startIndice(0)
	, numIndices(0)
	, numInstances(0)
	, startInstances(0)
{
}

GraphicsData::GraphicsData() noexcept
{
}

GraphicsData::~GraphicsData() noexcept
{
}

GraphicsStream::GraphicsStream(GraphicsData* data) noexcept
	: _data(data)
{
}

GraphicsStream::~GraphicsStream() noexcept
{
}

bool 
GraphicsStream::is_open() const noexcept
{
	return _data->is_open();
}

void 
GraphicsStream::resize(const char* data, std::size_t cnt) noexcept
{
	_data->resize(data, cnt);
}

streamsize
GraphicsStream::size() noexcept
{
	return _data->size();
}

int 
GraphicsStream::flush() noexcept
{
	return _data->flush();
}

int
GraphicsStream::flush(ios_base::off_type offset, streamsize cnt) noexcept
{
	return _data->flush(offset, cnt);
}

const char* 
GraphicsStream::map(std::uint32_t access) noexcept
{
	return _data->map(access);
}

const char*
GraphicsStream::map(ios_base::off_type offset, streamsize cnt, std::uint32_t access) noexcept
{
	return _data->map(offset, cnt, access);
}

void 
GraphicsStream::unmap() noexcept
{
	return _data->unmap();
}

bool 
GraphicsStream::isMapping() const noexcept
{
	return _data->isMapping();
}

VertexComponent::VertexComponent() noexcept
	: _attrib(VertexAttrib::GPU_ATTRIB_POSITION)
	, _format(VertexFormat::GPU_VERTEX_FLOAT)
{
}

VertexComponent::VertexComponent(VertexAttrib attrib, VertexFormat format) noexcept
	: _attrib(attrib)
	, _format(format)
{
}

VertexComponent::~VertexComponent() noexcept
{
}

void
VertexComponent::setVertexAttrib(VertexAttrib attrib) noexcept
{
	_attrib = attrib;
}

void
VertexComponent::setVertexFormat(VertexFormat format) noexcept
{
	_format = format;
}

VertexAttrib
VertexComponent::getVertexAttrib() const noexcept
{
	return _attrib;
}

VertexFormat
VertexComponent::getVertexFormat() const noexcept
{
	return _format;
}

int
VertexComponent::getVertexCount() const noexcept
{
	if (_format == VertexFormat::GPU_VERTEX_BYTE || _format == VertexFormat::GPU_VERTEX_UNSIGNED_BYTE ||
		_format == VertexFormat::GPU_VERTEX_SHORT || _format == VertexFormat::GPU_VERTEX_UNSIGNED_SHORT ||
		_format == VertexFormat::GPU_VERTEX_INT || _format == VertexFormat::GPU_VERTEX_UNSIGNED_INT ||
		_format == VertexFormat::GPU_VERTEX_FLOAT)
	{
		return 1;
	}
	else if (_format == VertexFormat::GPU_VERTEX_BYTE2 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_BYTE2 ||
		_format == VertexFormat::GPU_VERTEX_SHORT2 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_SHORT2 ||
		_format == VertexFormat::GPU_VERTEX_INT2 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_INT2 ||
		_format == VertexFormat::GPU_VERTEX_FLOAT2)
	{
		return 2;
	}
	else if (_format == VertexFormat::GPU_VERTEX_BYTE3 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_BYTE3 ||
		_format == VertexFormat::GPU_VERTEX_SHORT3 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_SHORT3 ||
		_format == VertexFormat::GPU_VERTEX_INT3 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_INT3 ||
		_format == VertexFormat::GPU_VERTEX_FLOAT3)
	{
		return 3;
	}
	else if (_format == VertexFormat::GPU_VERTEX_BYTE4 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_BYTE4 ||
		_format == VertexFormat::GPU_VERTEX_SHORT4 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_SHORT4 ||
		_format == VertexFormat::GPU_VERTEX_INT4 || _format == VertexFormat::GPU_VERTEX_UNSIGNED_INT4 ||
		_format == VertexFormat::GPU_VERTEX_FLOAT4)
	{
		return 4;
	}
	else
	{
		assert(false);
	}

	return 0;
}

int
VertexComponent::getVertexSize() const noexcept
{
	switch (_format)
	{
	case VertexFormat::GPU_VERTEX_BYTE:
	case VertexFormat::GPU_VERTEX_UNSIGNED_BYTE:
		return 1;
	case VertexFormat::GPU_VERTEX_SHORT:
	case VertexFormat::GPU_VERTEX_BYTE2:
	case VertexFormat::GPU_VERTEX_UNSIGNED_SHORT:
	case VertexFormat::GPU_VERTEX_UNSIGNED_BYTE2:
		return 2;
	case VertexFormat::GPU_VERTEX_BYTE3:
	case VertexFormat::GPU_VERTEX_UNSIGNED_BYTE3:
		return 3;
	case VertexFormat::GPU_VERTEX_FLOAT:
	case VertexFormat::GPU_VERTEX_INT:
	case VertexFormat::GPU_VERTEX_SHORT2:
	case VertexFormat::GPU_VERTEX_UNSIGNED_SHORT2:
	case VertexFormat::GPU_VERTEX_UNSIGNED_INT:
	case VertexFormat::GPU_VERTEX_UNSIGNED_BYTE4:
		return 4;
	case VertexFormat::GPU_VERTEX_SHORT3:
	case VertexFormat::GPU_VERTEX_UNSIGNED_SHORT3:
		return 6;
	case VertexFormat::GPU_VERTEX_INT2:
	case VertexFormat::GPU_VERTEX_SHORT4:
	case VertexFormat::GPU_VERTEX_FLOAT2:
	case VertexFormat::GPU_VERTEX_UNSIGNED_INT2:
	case VertexFormat::GPU_VERTEX_UNSIGNED_SHORT4:
		return 8;
	case VertexFormat::GPU_VERTEX_FLOAT3:
	case VertexFormat::GPU_VERTEX_INT3:
	case VertexFormat::GPU_VERTEX_UNSIGNED_INT3:
		return 12;
	case VertexFormat::GPU_VERTEX_FLOAT4:
	case VertexFormat::GPU_VERTEX_INT4:
	case VertexFormat::GPU_VERTEX_UNSIGNED_INT4:
		return 16;
	default:
		assert(false);
	}

	return 0;
}

VertexLayout::VertexLayout() noexcept
{
}

VertexLayout::~VertexLayout() noexcept
{
}

void
VertexLayout::setVertexComponents(const VertexComponents& component) noexcept
{
	_components = component;
}

const VertexComponents&
VertexLayout::getVertexComponents() const noexcept
{
	return _components;
}

void 
VertexLayout::addComponent(const VertexComponent& compoent) noexcept
{
	auto it = std::find_if(_components.begin(), _components.end(), [compoent](const VertexComponent& it) { return it.getVertexAttrib() == compoent.getVertexAttrib();});
	if (it == _components.end())
	{
		_components.push_back(compoent);
	}
}

void 
VertexLayout::removeComponent(const VertexComponent& compoent) noexcept
{
	auto it = std::find_if(_components.begin(), _components.end(), [compoent](const VertexComponent& it) { return it.getVertexAttrib() == compoent.getVertexAttrib();});
	if (it != _components.end())
	{
		_components.erase(it);
	}
}

std::uint32_t
VertexLayout::getVertexSize() const noexcept
{
	std::uint32_t _byteSize = 0;
	for (auto& it : _components)
	{
		_byteSize += it.getVertexSize();
	}

	return _byteSize;
}

VertexBufferData::VertexBufferData(GraphicsData* data) noexcept
	: GraphicsStream(data)
{
}

VertexBufferData::~VertexBufferData() noexcept
{
}

IndexBufferData::IndexBufferData(GraphicsData* data) noexcept
	: GraphicsStream(data)
{
}

IndexBufferData::~IndexBufferData() noexcept
{
}

RenderBuffer::RenderBuffer() noexcept
{
}

RenderBuffer::~RenderBuffer() noexcept
{
}

_NAME_END