#pragma once

#include <Vulkan/vulkan.hpp>

#include <filesystem>

namespace trg::vkwrappers
{
	std::vector<std::byte> readShaderCode(const std::filesystem::path& shaderPath);

	class Shader
	{
	public:
		Shader(vk::Device& device,
			   std::span<const std::byte> shaderCode,
			   vk::ShaderStageFlagBits shaderStage,
			   const std::string& entryPoint = "main");
		Shader(vk::Device& device,
			   const std::filesystem::path& shaderPath,
			   vk::ShaderStageFlagBits shaderStage,
			   const std::string& entryPoint = "main");

		vk::PipelineShaderStageCreateInfo getShaderStageCreateInfo() const;

	private:
		vk::UniqueShaderModule m_shaderModule;

		vk::ShaderStageFlagBits m_shaderStage;
		std::string m_entryPoint;
	};
}  // namespace trg::vkwrappers