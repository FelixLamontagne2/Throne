#pragma once

#include <Vulkan/vulkan.hpp>

#include <span>

namespace trg::vkwrappers
{
	class Fence
	{
	public:
		using VkHandleType = vk::Fence;

	public:
		explicit Fence(vk::Device& device);

		VkHandleType& getVkHandle();
		const VkHandleType& getVkHandle() const;

		VkHandleType& operator*();
		const VkHandleType& operator*() const;

		VkHandleType* operator->();
		const VkHandleType* operator->() const;

		void wait(uint64_t timeout = std::numeric_limits<uint64_t>::max());
		void reset();

		static void waitForFences(vk::Device& device,
								  std::span<Fence> fences,
								  bool waitForAll,
								  uint64_t timeout = std::numeric_limits<uint64_t>::max());
		static void resetFences(vk::Device& device, std::span<Fence> fences);

	private:
		std::reference_wrapper<vk::Device> m_device;

		vk::UniqueFence m_fence;
	};
}  // namespace trg::vkwrappers