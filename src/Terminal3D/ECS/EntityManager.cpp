#include "Terminal3D/ECS/EntityManager.h"

#ifndef NDEBUG // ifdef DEBUG

#define AssertEntityValid(entity) assert(entity >= 0 && entity < entitySize && "Entity is not in range")
#define AssertEntityValidInclusively(entity) assert(entity >= 0 && entity <= entitySize && "Entity is not in range inclusively")

#define AssertEntityReleased(entity)\
do\
{\
	bool isFree = false;\
	for(EntitySizeType i = firstReleasedEntityIndex; i < entitySize; ++i)\
	{\
		if (entities[i] == entity)\
		{\
			isFree = true;\
			break;\
		}\
	}\
	assert(isFree && "Entity is not free");\
} while (0);

#define AssertEntityAllocated(entity)\
do\
{\
	for(EntitySizeType i = firstReleasedEntityIndex; i < entitySize; ++i)\
	{\
		if (entities[i] == entity)\
		{\
			assert(false && "Entity is free"); \
		}\
	}\
} while (0);

#else

#define AssertEntityValid(entity)
#define AssertEntityValidInclusively(entity)
#define AssertEntityReleased(entity)
#define AssertEntityAllocated(entity)

#endif

ECS_NS::EntityManager::EntityManager(EntitySizeType entitySize)
	: entitySize(entitySize), firstReleasedEntityIndex(0)
{
	assert(entitySize > 0 && "Entity size is 0");

	entities = new Entity[entitySize];

	for (EntitySizeType e = 0; e < entitySize; ++e)
	{
		entities[e] = e;
	}
}

ECS_NS::Entity ECS_NS::EntityManager::Allocate()
{
	AssertEntityValid(firstReleasedEntityIndex);

	return entities[firstReleasedEntityIndex++];
}

void ECS_NS::EntityManager::Release(Entity entity)
{
	AssertEntityValid(entity);
	AssertEntityValid(firstReleasedEntityIndex - 1);
	AssertEntityAllocated(entity);

	entities[--firstReleasedEntityIndex] = entity;
}

ECS_NS::EntityManager::~EntityManager()
{
	delete[] entities;
}