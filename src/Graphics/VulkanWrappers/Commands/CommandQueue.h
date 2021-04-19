#pragma once

#include <Vulkan/vulkan.hpp>

namespace trg
{
	class CommandQueue
	{
	public:
		using VkHandleType = vk::Queue;

	public:
		CommandQueue() = default;
		CommandQueue(vk::Queue&& queue, uint32_t familyIndex);

		CommandQueue(const CommandQueue& other) = default;
		CommandQueue& operator=(const CommandQueue& other) = default;

		CommandQueue(CommandQueue&& other) = default;
		CommandQueue& operator=(CommandQueue&& other) = default;

		~CommandQueue() = default;

		VkHandleType& getVkHandle();
		const VkHandleType& getVkHandle() const;

		VkHandleType& operator*();
		const VkHandleType& operator*() const;

		VkHandleType* operator->();
		const VkHandleType* operator->() const;

		uint32_t getFamilyIndex() const;

	private:
		vk::Queue m_queue;
		uint32_t m_familyIndex = 0;
	};
}  // namespace trg