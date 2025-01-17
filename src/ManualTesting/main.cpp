#include <Core/Component.h>
#include <Core/Entity.h>
#include <Graphics/GraphicsInstance.h>
#include <Standard/CompressedPair.h>
#include <Standard/Manager.h>
#include <Standard/Pointers.h>

#include <boost/algorithm/string.hpp>
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <windows.h>

#include <iostream>
#include <optional>
#include <typeinfo>

//
using namespace std;
string ExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);  //
}

struct TestStruct
{
	TestStruct() = default;

	TestStruct(int a, int b)
	  : m_a(a)
	  , m_b(b)
	{
	}

	int m_a = 0;
	int m_b = 1;
};

class Health : public trc::Component<Health>
{
public:
	Health(trc::Entity& entity)
	  : Component(entity)
	{
	}
};

int main()
{
	// test 9
	std::cout << ExePath() << std::endl;
	std::cout << "Throne!" << std::endl;

	glm::vec3 vec3;
	vec3.x = 10;

	std::vector<std::string> vec;
	boost::join(vec, "/");

	gsl::not_null<int*> test = new int();
	delete test.get();

	auto str = fmt::format("{} {} {}", "test", "1", "3");

	std::cout << str << "\n";

	std::optional<int> opt;
	std::optional<int> opt2;  //

	trs::CompressedPair<int, double> pair1;
	pair1.first();
	pair1.second();

	class A
	{
	public:
		A(int i, double d, char c)
		{
			i = i + static_cast<int>(d) + c;
		}
	};

	trs::CompressedPair<A, A> pair2(std::piecewise_construct_t(), std::forward_as_tuple(3, 4.0, 'c'), std::forward_as_tuple(5, 2.0, 'b'));

	A a = A(5, 10.0, 'd');

	trs::CompressedPair<A, A> pair3(std::piecewise_construct_t(), std::forward_as_tuple(a), std::forward_as_tuple(5, 2.0, 'b'));

	pair2.first();

	//std::forward<int>(10);

	//std::pair<int, double> pair2;

	{
		std::shared_ptr<int> ptr = std::make_shared<int>();
	}

	{
		class Test
		{
		public:
			Test()
			{
			}

			~Test()
			{
				int a = 0;
				(void)a;
			}
		};

		std::weak_ptr<Test> wptr;
		{
			std::shared_ptr<Test> sptr = std::make_shared<Test>();
			wptr = sptr;
		}
	}

	{
		class B
		{
		public:
			B(int a)
			  : m_a(a)
			{
			}

			int m_a;
		};

		auto ptrOwner = trs::makePtrOwner<B>(10);
		ptrOwner->m_a;
	}

	{
		auto s1 = std::make_shared<int>(10);
		auto s2 = s1;
		s1 = std::move(s2);
	}

	{
		int* ptr = new int();
		auto o1 = trs::makePtrOwner<int>(ptr);
	}

	{
		trs::Manager<TestStruct> manager;

		manager.emplace(10, 11);
		manager.emplace(12, 13);
		manager.emplace(14, 15);
		manager.emplace(16, 17);
		manager.emplace(18, 19);
		manager.emplace(20, 21);

		__nop();
	}

	{
		trs::SharedPtr<int> shared1;
		auto shared2 = shared1;
	}

	{
		sizeof(Health);

		auto entity = trs::makePtrOwner<trc::Entity>();

		Health health(*entity);
		__nop();
	}
}
