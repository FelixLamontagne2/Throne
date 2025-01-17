#include "GraphicsPipeline.h"

#include "../../Utility.h"

namespace trg::vkwrappers
{
	namespace GraphicsPipelinePrivate
	{
		auto makePipelineLayout(vk::Device& device,
								const std::vector<std::reference_wrapper<const DescriptorSetLayout>>& descriptorSetLayouts,
								std::vector<vk::PushConstantRange> pushContants)
		{
			auto layouts = toVkHandle(descriptorSetLayouts);

			auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo({}, layouts, pushContants);

			return device.createPipelineLayoutUnique(pipelineLayoutCreateInfo);
		}

		auto makePipeline(vk::Device& device,
						  std::span<const Shader> shaders,
						  std::span<const VertexBufferSignature> bufferSignatures,
						  vk::PipelineInputAssemblyStateCreateInfo* inputAssemblyState,
						  vk::PipelineTessellationStateCreateInfo* tesselationState,
						  vk::PipelineViewportStateCreateInfo* viewportState,
						  vk::PipelineRasterizationStateCreateInfo* rasterizationState,
						  vk::PipelineMultisampleStateCreateInfo* multisampleState,
						  vk::PipelineDepthStencilStateCreateInfo* depthStencilState,
						  vk::PipelineColorBlendStateCreateInfo* colorBlendState,
						  vk::PipelineDynamicStateCreateInfo* dynamicState,
						  vk::PipelineLayout& pipelineLayout,
						  const RenderPass& renderPass)
		{
			std::vector<vk::PipelineShaderStageCreateInfo> shaderStageCreateInfos;
			for(const auto& shader: shaders)
			{
				shaderStageCreateInfos.emplace_back(shader.getShaderStageCreateInfo());
			}

			auto inputDescription = VertexBufferSignature::getInputBindingDescription(bufferSignatures);
			auto vertexInputState =
				vk::PipelineVertexInputStateCreateInfo({}, inputDescription.m_bindingDescription, inputDescription.m_attributeDescription);

			auto createInfo = vk::GraphicsPipelineCreateInfo({},
															 shaderStageCreateInfos,
															 &vertexInputState,
															 inputAssemblyState,
															 tesselationState,
															 viewportState,
															 rasterizationState,
															 multisampleState,
															 depthStencilState,
															 colorBlendState,
															 dynamicState,
															 pipelineLayout,
															 *renderPass);

			auto cacheCreateInfo = vk::PipelineCacheCreateInfo();
			auto cache = device.createPipelineCacheUnique(cacheCreateInfo);

			return device.createGraphicsPipelineUnique(*cache, createInfo).value;
		}
	}  // namespace GraphicsPipelinePrivate


	GraphicsPipeline::GraphicsPipeline(vk::Device& device,
									   const std::vector<std::reference_wrapper<const DescriptorSetLayout>>& descriptorSetLayouts,
									   std::vector<vk::PushConstantRange> pushContants,
									   std::span<const Shader> shaders,
									   std::span<const VertexBufferSignature> bufferSignatures,
									   vk::PipelineInputAssemblyStateCreateInfo* inputAssemblyState,
									   vk::PipelineTessellationStateCreateInfo* tesselationState,
									   vk::PipelineViewportStateCreateInfo* viewportState,
									   vk::PipelineRasterizationStateCreateInfo* rasterizationState,
									   vk::PipelineMultisampleStateCreateInfo* multisampleState,
									   vk::PipelineDepthStencilStateCreateInfo* depthStencilState,
									   vk::PipelineColorBlendStateCreateInfo* colorBlendState,
									   vk::PipelineDynamicStateCreateInfo* dynamicState,
									   const RenderPass& renderPass)
	  : m_layout(GraphicsPipelinePrivate::makePipelineLayout(device, descriptorSetLayouts, pushContants))
	  , m_pipeline(GraphicsPipelinePrivate::makePipeline(device,
														 shaders,
														 bufferSignatures,
														 inputAssemblyState,
														 tesselationState,
														 viewportState,
														 rasterizationState,
														 multisampleState,
														 depthStencilState,
														 colorBlendState,
														 dynamicState,
														 *m_layout,
														 renderPass))
	{
	}

	void GraphicsPipeline::bind(BindableBindInfo& bindInfo)
	{
		bindInfo.m_commandBuffer->bindPipeline(vk::PipelineBindPoint::eGraphics, *m_pipeline);
		m_dynamicStates.bind(bindInfo);
	}

	vk::PipelineLayout& GraphicsPipeline::getLayout()
	{
		return *m_layout;
	}

	PipelineDynamicStates& GraphicsPipeline::getPipelineDynamicStates()
	{
		return m_dynamicStates;
	}

	const PipelineDynamicStates& GraphicsPipeline::getPipelineDynamicStates() const
	{
		return m_dynamicStates;
	}
}  // namespace trg::vkwrappers