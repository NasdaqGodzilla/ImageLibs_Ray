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
#include "vk_render_pipeline.h"
#include "vk_device.h"
#include "vk_shader.h"
#include "vk_input_layout.h"
#include "vk_framebuffer.h"
#include "vk_descriptor_set_layout.h"
#include "vk_system.h"

_NAME_BEGIN

__ImplementSubClass(VulkanRenderPipeline, GraphicsPipeline, "VulkanRenderPipeline")

VulkanRenderPipeline::VulkanRenderPipeline() noexcept
	: _vkPipeline(VK_NULL_HANDLE)
	, _vkPipelineCache(VK_NULL_HANDLE)
	, _vkPipelineLayout(VK_NULL_HANDLE)
{
}

VulkanRenderPipeline::~VulkanRenderPipeline() noexcept
{
	this->close();
}

bool
VulkanRenderPipeline::setup(const GraphicsPipelineDesc& pipelineDesc) noexcept
{
	assert(pipelineDesc.getGraphicsDescriptorSetLayout());
	assert(pipelineDesc.getGraphicsFramebufferLayout());
	assert(pipelineDesc.getGraphicsProgram());
	assert(pipelineDesc.getGraphicsInputLayout());
	assert(pipelineDesc.getGraphicsState());

	VkGraphicsPipelineCreateInfo pipeline;
	VkPipelineCacheCreateInfo pipelineCache;
	VkPipelineVertexInputStateCreateInfo vi;
	VkPipelineInputAssemblyStateCreateInfo ia;
	VkPipelineRasterizationStateCreateInfo rs;
	VkPipelineColorBlendStateCreateInfo cb;
	VkPipelineDepthStencilStateCreateInfo ds;
	VkPipelineViewportStateCreateInfo vp;
	VkPipelineTessellationStateCreateInfo ts;
	VkPipelineMultisampleStateCreateInfo ms;
	VkPipelineDynamicStateCreateInfo dynamicState;
	VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
	VkPipelineShaderStageCreateInfo shaderStages[GraphicsShaderStage::GraphicsShaderStageRangeSize];

	std::vector<VkVertexInputBindingDescription> vibs;
	std::vector<VkVertexInputAttributeDescription> vias;

	const auto& stateDesc = pipelineDesc.getGraphicsState()->getGraphicsStateDesc();
	const auto& inputLayoutDesc = pipelineDesc.getGraphicsInputLayout()->getGraphicsInputLayoutDesc();
	const auto& programDesc = pipelineDesc.getGraphicsProgram()->getGraphicsProgramDesc();

	const auto& stencilState = stateDesc.getStencilState();
	const auto& depthState = stateDesc.getDepthState();
	const auto& rasterState = stateDesc.getRasterState();
	
	memset(&pipeline, 0, sizeof(pipeline));
	memset(&pipelineCache, 0, sizeof(pipelineCache));
	memset(&vi, 0, sizeof(vi));
	memset(&ia, 0, sizeof(ia));
	memset(&rs, 0, sizeof(rs));
	memset(&cb, 0, sizeof(cb));
	memset(&ds, 0, sizeof(ds));
	memset(&vp, 0, sizeof(vp));
	memset(&ts, 0, sizeof(ts));
	memset(&ms, 0, sizeof(ms));
	memset(&dynamicState, 0, sizeof(dynamicState));
	memset(&dynamicStateEnables[0], 0, sizeof(dynamicStateEnables));
	memset(&shaderStages[0], 0, sizeof(shaderStages));

	VkVertexInputBindingDescription vib;
	vib.binding = 0;
	vib.stride = inputLayoutDesc.getVertexSize();
	vib.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	vibs.push_back(vib);

	std::uint32_t offset = 0;
	const auto& components = inputLayoutDesc.getGraphicsVertexLayouts();
	for (auto& component : components)
	{
		VkVertexInputAttributeDescription attr;
		attr.binding = component.getVertexSlot();
		attr.location = component.getSemanticIndex();
		attr.offset = offset;
		attr.format = VulkanTypes::asGraphicsFormat(component.getVertexFormat());

		offset += component.getVertexSize();

		vias.push_back(attr);
	}

	vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vi.vertexBindingDescriptionCount = vibs.size();
	vi.vertexAttributeDescriptionCount = vias.size();
	vi.pVertexBindingDescriptions = vibs.data();
	vi.pVertexAttributeDescriptions = vias.data();

	ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ia.topology = VulkanTypes::asPrimitiveTopology(rasterState.primitiveType);

	rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rs.cullMode = VulkanTypes::asCullMode(rasterState.cullMode);
	rs.frontFace = VulkanTypes::asFrontFace(rasterState.frontFace);
	rs.polygonMode = VulkanTypes::asPolygonMode(rasterState.polygonMode);
	rs.rasterizerDiscardEnable = rasterState.rasterizerDiscardEnable;
	rs.depthBiasEnable = depthState.depthBiasEnable;
	rs.depthBiasConstantFactor = depthState.depthBias;
	rs.depthClampEnable = depthState.depthClampEnable;
	rs.depthBiasClamp = depthState.depthBiasClamp;
	rs.depthBiasSlopeFactor = depthState.depthSlopeScaleBias;

	cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

	ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	ds.depthTestEnable = depthState.depthEnable;
	ds.depthWriteEnable = depthState.depthWriteEnable;
	ds.depthCompareOp = VulkanTypes::asCompareOp(depthState.depthFunc);
	ds.depthBoundsTestEnable = depthState.depthBoundsEnable;
	ds.minDepthBounds = depthState.depthMin;
	ds.maxDepthBounds = depthState.depthMax;
	ds.stencilTestEnable = stencilState.stencilEnable;
	ds.front.compareMask = stencilState.stencilReadMask;
	ds.front.compareOp = VulkanTypes::asCompareOp(stencilState.stencilFunc);
	ds.front.depthFailOp = VulkanTypes::asStencilOp(stencilState.stencilZFail);
	ds.front.failOp = VulkanTypes::asStencilOp(stencilState.stencilFail);
	ds.front.passOp = VulkanTypes::asStencilOp(stencilState.stencilPass);
	ds.front.reference = stencilState.stencilRef;
	ds.front.writeMask = stencilState.stencilWriteMask;
	ds.back.compareMask = stencilState.stencilTwoEnable ? stencilState.stencilTwoReadMask : ds.front.compareMask;
	ds.back.compareOp = stencilState.stencilTwoEnable ? VulkanTypes::asCompareOp(stencilState.stencilTwoFunc) : ds.front.compareOp;
	ds.back.depthFailOp = stencilState.stencilTwoEnable ? VulkanTypes::asStencilOp(stencilState.stencilTwoZFail) : ds.front.depthFailOp ;
	ds.back.failOp = stencilState.stencilTwoEnable ? VulkanTypes::asStencilOp(stencilState.stencilTwoFail) : ds.front.failOp;
	ds.back.passOp = stencilState.stencilTwoEnable ? VulkanTypes::asStencilOp(stencilState.stencilTwoPass) : ds.front.passOp;
	ds.back.reference = stencilState.stencilTwoEnable ? stencilState.stencilTwoRef : ds.front.reference;
	ds.back.writeMask = stencilState.stencilTwoEnable ? stencilState.stencilTwoWriteMask : ds.front.writeMask;

	vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vp.viewportCount = 1;
	vp.scissorCount = 1;

	ts.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

	ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	ms.sampleShadingEnable = rasterState.multisampleEnable;

	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.pDynamicStates = dynamicStateEnables;

	dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
	dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

	for (const auto& shader : programDesc.getShaders())
	{
		auto module = shader->downcast<VulkanShader>();

		shaderStages[pipeline.stageCount].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStages[pipeline.stageCount].module = module->getShaderModule();
		shaderStages[pipeline.stageCount].stage = VulkanTypes::asShaderStage(module->getGraphicsShaderDesc().getType());
		shaderStages[pipeline.stageCount].pName = "main";

		pipeline.stageCount++;
	}

	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.pNext = nullptr;
	pipeline.pVertexInputState = &vi;
	pipeline.pInputAssemblyState = &ia;
	pipeline.pRasterizationState = &rs;
	pipeline.pColorBlendState = &cb;
	pipeline.pDepthStencilState = &ds;
	pipeline.pViewportState = &vp;
	pipeline.pTessellationState = &ts;
	pipeline.pMultisampleState = &ms;
	pipeline.pStages = shaderStages;	
	pipeline.pDynamicState = &dynamicState;
	pipeline.renderPass = pipelineDesc.getGraphicsFramebufferLayout()->downcast<VulkanFramebufferLayout>()->getRenderPass();

	VkDescriptorSetLayout descriptorSetLayout;
	descriptorSetLayout = pipelineDesc.getGraphicsDescriptorSetLayout()->downcast<VulkanDescriptorSetLayout>()->getDescriptorSetLayout();

	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo;
	pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreateInfo.pNext = nullptr;
	pipelineLayoutCreateInfo.flags = 0;
	pipelineLayoutCreateInfo.setLayoutCount = 1;
	pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;
	pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

	if (vkCreatePipelineLayout(this->getDevice()->downcast<VulkanDevice>()->getDevice(), &pipelineLayoutCreateInfo, nullptr, &_vkPipelineLayout) != VK_SUCCESS)
	{
		VK_PLATFORM_LOG("vkCreatePipelineLayout() fail.");
		return false;
	}

	pipelineCache.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
	if (vkCreatePipelineCache(this->getDevice()->downcast<VulkanDevice>()->getDevice(), &pipelineCache, nullptr, &_vkPipelineCache) != VK_SUCCESS)
	{
		VK_PLATFORM_LOG("vkCreatePipelineCache() fail.");
		return false;
	}

	pipeline.layout = _vkPipelineLayout;
	if (vkCreateGraphicsPipelines(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkPipelineCache, 1, &pipeline, nullptr, &_vkPipeline) != VK_SUCCESS)
	{
		VK_PLATFORM_LOG("vkCreateGraphicsPipelines() fail.");
		return false;
	}

	_pipelineDesc = pipelineDesc;
	return true;
}

void 
VulkanRenderPipeline::close() noexcept
{
	if (_vkPipelineCache != VK_NULL_HANDLE)
	{
		vkDestroyPipelineCache(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkPipelineCache, nullptr);
		_vkPipelineCache = VK_NULL_HANDLE;
	}

	if (_vkPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _vkPipeline, nullptr);
		_vkPipeline = VK_NULL_HANDLE;
	}
}

VkPipeline
VulkanRenderPipeline::getPipeline() const noexcept
{
	return _vkPipeline;
}

VkPipelineLayout
VulkanRenderPipeline::getPipelineLayout() const noexcept
{
	return _vkPipelineLayout;
}

void
VulkanRenderPipeline::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
VulkanRenderPipeline::getDevice() noexcept
{
	return _device.lock();
}

const GraphicsPipelineDesc& 
VulkanRenderPipeline::getGraphicsPipelineDesc() const noexcept
{
	return _pipelineDesc;
}

_NAME_END