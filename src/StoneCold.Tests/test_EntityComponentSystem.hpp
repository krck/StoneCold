
#include "pch.h"
#include "EntityComponentSystem.hpp"
#include <vector>

using StoneCold::Engine::EntityComponentSystem;

//
// ...
//
TEST(EntityComponentSystem, InitializeAndCreateEntity) {
	EntityComponentSystem ecs{};
	ecs.Init();

	auto e1 = ecs.CreateEntity();
	auto e2 = ecs.CreateEntity();
	auto e3 = ecs.CreateEntity();

	ASSERT_EQ(e1, 0);
	ASSERT_EQ(e2, 1);
	ASSERT_EQ(e3, 2);
}

//
// ...
//
TEST(EntityComponentSystem, CreateAllEntitiesAndMore) {
	EntityComponentSystem ecs{};
	ecs.Init();

	auto testEs = std::vector<uint32_t>();
	testEs.reserve(MAX_ENTITIES + 10);

	for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
		testEs.push_back(ecs.CreateEntity());
	}

	ASSERT_EQ(ecs.AvailableEntitiesSize(), 0);
	ASSERT_ANY_THROW(ecs.CreateEntity()) << "Failed to throw when no more Entity Ids are available";
}




