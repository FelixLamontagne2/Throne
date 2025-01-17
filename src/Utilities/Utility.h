#pragma once

#include <algorithm>
#include <cassert>
#include <span>
#include <type_traits>

namespace tru
{
	template <typename DstType, typename SrcType>
	DstType staticDownCast(SrcType& src)
	{
		assert(dynamic_cast<std::add_pointer_t<std::remove_reference_t<DstType>>>(&src) != nullptr);
		return static_cast<DstType>(src);
	}

	/// <summary>
	/// Apply a function on an atomic if the predicate returns true.
	/// </summary>
	template <typename Func, typename Predicate, typename AtomicType>
	bool applyIf(AtomicType& atomic, Func func, Predicate pred) noexcept
	{
		auto tempVal = atomic.load();
		while(pred(tempVal))
		{
			if(atomic.compare_exchange_weak(tempVal, func(tempVal)))
			{
				return true;
			}
		}
		return false;
	}

	template <auto comparedValue, typename AtomicType>
	bool incrementNotEqual(AtomicType& atomic) noexcept
	{
		return applyIf(
			atomic,
			[](auto value) {
				return value + 1;
			},
			[](auto value) {
				return value != comparedValue;
			});
	}

	template <auto comparedValue, typename AtomicType>
	bool decrementEqual(AtomicType& atomic) noexcept
	{
		return applyIf(
			atomic,
			[](auto value) {
				return value - 1;
			},
			[](auto value) {
				return value == comparedValue;
			});
	}

	template <typename T>
	bool allEqual(std::span<const T> values)
	{
		return std::adjacent_find(values.cbegin(), values.cend(), std::not_equal_to()) == values.end();
	}
}  // namespace tru