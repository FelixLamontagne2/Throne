#include <Core/Entity.h>
#include <Tests/ProxyGmock.h>

#include <catch.hpp>

namespace Tests
{
	SCENARIO("TestAddChild", "Entity")
	{
		GIVEN("An entity with no child")
		{
			auto child = trs::makePtrOwner<trc::Entity>();
			auto entity = trs::makePtrOwner<trc::Entity>();
			WHEN("Adding a child")
			{
				entity->addChild(*child);
				THEN("The child is added")
				{
					const auto& children = entity->getChildren();
					REQUIRE(children.size() == 1);
					REQUIRE(children[0] == child);
				}
				AND_THEN("The child's parent is set")
				{
					REQUIRE(child->getTopParent() == entity);
					REQUIRE(child->getParent() == entity);
				}
			}
		}
	}

	SCENARIO("TestRemoveChild", "Entity")
	{
		GIVEN("An entity with one child")
		{
			auto entity = trs::makePtrOwner<trc::Entity>();
			auto child = trs::makePtrOwner<trc::Entity>();

			entity->addChild(*child);
			WHEN("Removing the child")
			{
				entity->removeChild(*child);
				THEN("The child is removed")
				{
					const auto& children = entity->getChildren();
					REQUIRE(children.empty());
				}
				AND_THEN("The child's parent is removed")
				{
					REQUIRE(child->getTopParent() == nullptr);
					REQUIRE(child->getParent() == nullptr);
				}
			}
		}
		GIVEN("An entity with many children")
		{
			auto child1 = trs::makePtrOwner<trc::Entity>();
			auto child2 = trs::makePtrOwner<trc::Entity>();
			auto child3 = trs::makePtrOwner<trc::Entity>();
			auto entity = trs::makePtrOwner<trc::Entity>();

			entity->addChild(*child1);
			entity->addChild(*child2);
			entity->addChild(*child3);
			WHEN("Removing the first child")
			{
				entity->removeChild(*child1);
				THEN("The child is removed")
				{
					const auto& children = entity->getChildren();
					REQUIRE(children.size() == 2);
					REQUIRE(children[0] == child2);
					REQUIRE(children[1] == child3);
				}
				AND_THEN("The child's parent is removed")
				{
					REQUIRE(child1->getTopParent() == nullptr);
					REQUIRE(child1->getParent() == nullptr);
				}
			}
			WHEN("Removing the middle child")
			{
				entity->removeChild(*child2);
				THEN("The child is removed")
				{
					const auto& children = entity->getChildren();
					REQUIRE(children.size() == 2);
					REQUIRE(children[0] == child1);
					REQUIRE(children[1] == child3);
				}
				AND_THEN("The child's parent is removed")
				{
					REQUIRE(child2->getTopParent() == nullptr);
					REQUIRE(child2->getParent() == nullptr);
				}
			}
			WHEN("Removing the last child")
			{
				entity->removeChild(*child3);
				THEN("The child is removed")
				{
					const auto& children = entity->getChildren();
					REQUIRE(children.size() == 2);
					REQUIRE(children[0] == child1);
					REQUIRE(children[1] == child2);
				}
				AND_THEN("The child's parent is removed")
				{
					REQUIRE(child3->getTopParent() == nullptr);
					REQUIRE(child3->getParent() == nullptr);
				}
			}
		}
	}

	SCENARIO("TestSetParent", "Entity")
	{
		GIVEN("An entity with no parent")
		{
			auto entity = trs::makePtrOwner<trc::Entity>();
			auto parent = trs::makePtrOwner<trc::Entity>();

			WHEN("Setting it's parent to an existing Entity")
			{
				entity->setParent(*parent);
				THEN("The parent is set")
				{
					REQUIRE(entity->getTopParent() == parent);
					REQUIRE(entity->getParent() == parent);
				}
				AND_THEN("The parent's child is added")
				{
					const auto& children = parent->getChildren();
					REQUIRE(children.size() == 1);
					REQUIRE(children[0] == entity);
				}
			}
		}
		GIVEN("An entity with a parent")
		{
			auto entity = trs::makePtrOwner<trc::Entity>();
			auto parent = trs::makePtrOwner<trc::Entity>();

			entity->setParent(*parent);

			WHEN("Setting it's parent to a nullopt")
			{
				entity->setParent(std::nullopt);
				THEN("The parent is removed")
				{
					REQUIRE(entity->getTopParent() == nullptr);
					REQUIRE(entity->getParent() == nullptr);
				}
				AND_THEN("The child is removed from its parent")
				{
					const auto& children = parent->getChildren();
					REQUIRE(children.size() == 0);
				}
			}
			WHEN("Setting it's parent to another Entity")
			{
				auto parent2 = trs::makePtrOwner<trc::Entity>();

				entity->setParent(*parent2);

				THEN("The parent is set")
				{
					REQUIRE(entity->getTopParent() == parent2);
					REQUIRE(entity->getParent() == parent2);
				}
				AND_THEN("The parent's child is added")
				{
					const auto& children = parent2->getChildren();
					REQUIRE(children.size() == 1);
					REQUIRE(children[0] == entity);
				}
				AND_THEN("The child is removed from the old parent")
				{
					const auto& children = parent->getChildren();
					REQUIRE(children.size() == 0);
				}
			}
		}
	}

	SCENARIO("TestTopParent", "Entity")
	{
		// Entity
		// |
		// --> Child1
		//     |
		//	   --> Child2 (topParent == Entity1)
		GIVEN("An entity with a child1")
		{
			auto child2 = trs::makePtrOwner<trc::Entity>();
			auto child1 = trs::makePtrOwner<trc::Entity>();
			auto entity = trs::makePtrOwner<trc::Entity>();
			entity->addChild(*child1);
			WHEN("Adding a child2 to child1")
			{
				child1->addChild(*child2);
				THEN("Child2 top parent is equal to entity1")
				{
					REQUIRE(child2->getTopParent() == entity);
					REQUIRE(child2->getParent() == child1);
				}
			}
		}
	}
}  // namespace Tests