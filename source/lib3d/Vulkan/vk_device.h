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
#ifndef _H_VK_DEVICE_H_
#define _H_VK_DEVICE_H_

#include "vk_types.h"

_NAME_BEGIN

class VulkanDevice final : public GraphicsDevice2
{
	__DeclareSubClass(VulkanDevice, GraphicsDevice2)
public:
	VulkanDevice() noexcept;
	virtual ~VulkanDevice() noexcept;

	bool setup(const GraphicsDeviceDesc& desc) noexcept;
	void close() noexcept;

	VkDevice getDevice() const noexcept;
	VkPhysicalDevice getPhysicalDevice() const noexcept;

	GraphicsSwapchainPtr createSwapchain(const GraphicsSwapchainDesc& desc) noexcept;
	GraphicsContextPtr createDeviceContext(const GraphicsContextDesc& desc) noexcept;
	GraphicsInputLayoutPtr createInputLayout(const GraphicsInputLayoutDesc& desc) noexcept;
	GraphicsDataPtr createGraphicsData(const GraphicsDataDesc& desc) noexcept;
	GraphicsTexturePtr createTexture(const GraphicsTextureDesc& desc) noexcept;
	GraphicsSamplerPtr createSampler(const GraphicsSamplerDesc& desc) noexcept;
	GraphicsFramebufferPtr createFramebuffer(const GraphicsFramebufferDesc& desc) noexcept;
	GraphicsFramebufferLayoutPtr createFramebufferLayout(const GraphicsFramebufferLayoutDesc& desc) noexcept;
	GraphicsStatePtr createRenderState(const GraphicsStateDesc& desc) noexcept;
	GraphicsShaderPtr createShader(const GraphicsShaderDesc& desc) noexcept;
	GraphicsProgramPtr createProgram(const GraphicsProgramDesc& desc) noexcept;
	GraphicsPipelinePtr createRenderPipeline(const GraphicsPipelineDesc& desc) noexcept;
	GraphicsDescriptorPoolPtr createDescriptorPool(const GraphicsDescriptorPoolDesc& desc) noexcept;
	GraphicsDescriptorSetPtr createDescriptorSet(const GraphicsDescriptorSetDesc& desc) noexcept;
	GraphicsDescriptorSetLayoutPtr createDescriptorSetLayout(const GraphicsDescriptorSetLayoutDesc& desc) noexcept;
	GraphicsCommandQueuePtr createCommandQueue(const GraphicsCommandQueueDesc& desc) noexcept;
	GraphicsCommandPoolPtr createCommandPool(const GraphicsCommandPoolDesc& desc) noexcept;
	GraphicsCommandListPtr createCommandList(const GraphicsCommandListDesc& desc) noexcept;
	GraphicsSemaphorePtr createSemaphore(const GraphicsSemaphoreDesc& desc) noexcept;

	void copyDescriptorSets(GraphicsDescriptorSetPtr& source, std::uint32_t descriptorCopyCount, const GraphicsDescriptorSetPtr descriptorCopies[]) noexcept;

	const GraphicsDeviceProperty& getGraphicsDeviceProperty() const noexcept;
	const GraphicsDeviceDesc& getGraphicsDeviceDesc() const noexcept;

private:
	VulkanDevice(const VulkanDevice&) noexcept = delete;
	VulkanDevice& operator=(const VulkanDevice&) noexcept = delete;

private:
	VkDevice _device;
	GraphicsDeviceDesc _deviceDesc;
	VulkanDevicePropertyPtr _physicalDevice;
};

_NAME_END

#endif