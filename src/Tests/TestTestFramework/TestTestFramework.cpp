#include <catch.hpp>

#include <thread>

namespace Tests
{
	unsigned int Factorial(unsigned int number)
	{
		return number > 1 ? Factorial(number - 1) * number : 1;
	}

	TEST_CASE("Factorials are computed", "[factorial]")
	{
		REQUIRE(Factorial(0) == 1);
		REQUIRE(Factorial(1) == 1);
		REQUIRE(Factorial(2) == 2);
		REQUIRE(Factorial(3) == 6);
		REQUIRE(Factorial(10) == 3628800);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	TEST_CASE("vectors can be sized and resized", "[vector]")
	{
		std::vector<int> v(5);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 5);

		SECTION("resizing bigger changes size and capacity")
		{
			v.resize(10);

			REQUIRE(v.size() == 10);
			REQUIRE(v.capacity() >= 10);
		}
		SECTION("resizing smaller changes size but not capacity")
		{
			v.resize(0);

			REQUIRE(v.size() == 0);
			REQUIRE(v.capacity() >= 5);
		}
		SECTION("reserving bigger changes capacity but not size")
		{
			v.reserve(10);

			REQUIRE(v.size() == 5);
			REQUIRE(v.capacity() >= 10);
		}
		SECTION("reserving smaller does not change size or capacity")
		{
			v.reserve(0);

			REQUIRE(v.size() == 5);
			REQUIRE(v.capacity() >= 5);
		}
	}

	SCENARIO("vectors can be sized and resized", "[vector]")
	{
		GIVEN("A vector with some items")
		{
			std::vector<int> v(5);

			REQUIRE(v.size() == 5);
			REQUIRE(v.capacity() >= 5);

			WHEN("the size is increased")
			{
				v.resize(10);

				THEN("the size and capacity change")
				{
					REQUIRE(v.size() == 10);
					REQUIRE(v.capacity() >= 10);
				}
			}
			WHEN("the size is reduced")
			{
				v.resize(0);

				THEN("the size changes but not capacity")
				{
					REQUIRE(v.size() == 0);
					REQUIRE(v.capacity() >= 5);
				}
			}
			WHEN("more capacity is reserved")
			{
				v.reserve(10);

				THEN("the capacity changes but not the size")
				{
					REQUIRE(v.size() == 5);
					REQUIRE(v.capacity() >= 10);
				}
			}
			WHEN("less capacity is reserved")
			{
				v.reserve(0);

				THEN("neither size nor capacity are changed")
				{
					REQUIRE(v.size() == 5);
					REQUIRE(v.capacity() >= 5);
				}
			}
		}
	}
}  // namespace Tests