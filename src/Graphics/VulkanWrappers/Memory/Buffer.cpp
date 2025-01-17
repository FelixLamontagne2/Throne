#include "Buffer.h"

#include "VmaAllocator.h"

namespace trg::vkwrappers
{
	namespace BufferPrivate
	{
		auto makeBuffer(vk::DeviceSize bufferSize, vk::BufferUsageFlagBits bufferUsage, vma::MemoryUsage memoryUsage)
		{
			vk::BufferCreateInfo bufferInfo = vk::BufferCreateInfo({}, bufferSize, bufferUsage);

			vma::AllocationCreateInfo allocationCreateInfo = vma::AllocationCreateInfo();
			allocationCreateInfo.usage = memoryUsage;

			return g_vmaDefaultAllocator.createBuffer(bufferInfo, allocationCreateInfo);
		}
	}  // namespace BufferPrivate

	Buffer::Buffer(vk::DeviceSize bufferSize, vk::BufferUsageFlagBits bufferUsage, vma::MemoryUsage memoryUsage)
	  : m_buffer(BufferPrivate::makeBuffer(bufferSize, bufferUsage, memoryUsage))
	{
	}

	void Buffer::updateWithHostMemory(tru::MemoryRegion memory)
	{
		allocateHostMemory(memory, m_buffer.m_allocation);
	}

	Buffer::VkHandleType& Buffer::getVkHandle()
	{
		return m_buffer.m_value;
	}

	const Buffer::VkHandleType& Buffer::getVkHandle() const
	{
		return m_buffer.m_value;
	}

	Buffer::VkHandleType& Buffer::operator*()
	{
		return getVkHandle();
	}

	const Buffer::VkHandleType& Buffer::operator*() const
	{
		return getVkHandle();
	}

	Buffer::VkHandleType* Buffer::operator->()
	{
		return &getVkHandle();
	}

	const Buffer::VkHandleType* Buffer::operator->() const
	{
		return &getVkHandle();
	}
}  // namespace trg::vkwrappers