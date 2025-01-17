// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#ifndef _H_OGL_DESCRIPTOR_H_
#define _H_OGL_DESCRIPTOR_H_

#include "ogl_types.h"

_NAME_BEGIN

class OGLCoreDescriptorSet final : public GraphicsDescriptorSet
{
	__DeclareSubClass(OGLCoreDescriptorSet, OGLCoreGraphicsData)
public:
	OGLCoreDescriptorSet() noexcept;
	~OGLCoreDescriptorSet() noexcept;

	bool setup(const GraphicsDescriptorSetDesc& desc) noexcept;
	void close() noexcept;

	void apply(const OGLProgram& shaderObject) noexcept;

	void copy(std::uint32_t descriptorCopyCount, const GraphicsDescriptorSetPtr descriptorCopies[]) noexcept;

	const GraphicsUniformSets& getGraphicsUniformSets() const noexcept;
	const GraphicsDescriptorSetDesc& getGraphicsDescriptorSetDesc() const noexcept;

private:
	friend class OGLDevice;
	void setDevice(const GraphicsDevicePtr& device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

private:
	OGLCoreDescriptorSet(const OGLCoreDescriptorSet&) noexcept = delete;
	OGLCoreDescriptorSet& operator=(const OGLCoreDescriptorSet&) noexcept = delete;

private:
	GraphicsUniformSets _activeUniformSets;
	GraphicsDeviceWeakPtr _device;
	GraphicsDescriptorSetDesc _descriptorSetDesc;
};

_NAME_END

#endif