#pragma once

#include "ECSCore.h"

#include <cstddef>
#include <cassert>
#include <cstdint>

ECS_NAMESPACE_BEGIN

using Entity = uint32_t;
using EntitySizeType = Entity;

class EntityManager
{
public:
	static constexpr Entity InvalidEntity = ~0;

	EntityManager(EntitySizeType entitySize = 1000);

	Entity Allocate();

	void Release(Entity entity);

	~EntityManager();

private:
	
	const EntitySizeType entitySize;
	Entity* entities;
	EntitySizeType firstReleasedEntityIndex;
};

ECS_NAMESPACE_END