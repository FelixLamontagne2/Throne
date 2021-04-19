#include "VmaAllocator.h"

namespace trg
{
	vma::Allocator g_vmaDefaultAllocator;

	namespace VmaAllocatorPrivate
	{
		vma::VulkanFunctions getVulkanFunctions()
		{
#define SET_FUNCTION(funcName) vulkanFunctions.funcName = vk::defaultDispatchLoaderDynamic.funcName;

			vma::VulkanFunctions vulkanFunctions;
			SET_FUNCTION(vkGetPhysicalDeviceProperties);
			SET_FUNCTION(vkGetPhysicalDeviceMemoryProperties);
			SET_FUNCTION(vkAllocateMemory);
			SET_FUNCTION(vkFreeMemory);
			SET_FUNCTION(vkMapMemory);
			SET_FUNCTION(vkUnmapMemory);
			SET_FUNCTION(vkFlushMappedMemoryRanges);
			SET_FUNCTION(vkInvalidateMappedMemoryRanges);
			SET_FUNCTION(vkBindBufferMemory);
			SET_FUNCTION(vkBindImageMemory);
			SET_FUNCTION(vkGetBufferMemoryRequirements);
			SET_FUNCTION(vkGetImageMemoryRequirements);
			SET_FUNCTION(vkCreateBuffer);
			SET_FUNCTION(vkDestroyBuffer);
			SET_FUNCTION(vkCreateImage);
			SET_FUNCTION(vkDestroyImage);
			SET_FUNCTION(vkCmdCopyBuffer);

#undef SET_FUNCTION

			return vulkanFunctions;
		}
	}  // namespace VmaAllocatorPrivate

	void initializeVmaDefaultAllocator(vk::PhysicalDevice& physicalDevice, vk::Device& device)
	{
		auto allocatorCreateInfo = vma::AllocatorCreateInfo({}, physicalDevice, device);

		vma::VulkanFunctions vulkanFunctions = VmaAllocatorPrivate::getVulkanFunctions();

		allocatorCreateInfo.setPVulkanFunctions(&vulkanFunctions);

		g_vmaDefaultAllocator = vma::createAllocator(allocatorCreateInfo);
	}
}  // namespace trg