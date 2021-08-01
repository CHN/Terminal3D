#pragma once

#include <cstddef>
#include <cassert>

using Entity = size_t;

template<typename T, size_t Size = 500>
class EntityManager
{
#define AssertEntityValid(entity) assert(entity >= 0 && entity < Size);

public:

	static constexpr Entity InvalidEntity = ~0;

	template<typename ...Ts>
	Entity AddComponent(const Ts&... ts)
	{
		if (minimumLastFreedEntity < lastEntity)
		{
			AllocateAtIndex(minimumLastFreedEntity, ts...);
			size_t temp = minimumLastFreedEntity;
			minimumLastFreedEntity = Size;
			return temp;
		}

		if (lastEntity < Size)
		{
			AllocateAtIndex(lastEntity, ts...);
			return lastEntity++;
		}

		for (size_t i = Size-1; i >= 0; --i)
		{
			if (!allocateInfos[i])
			{
				AllocateAtIndex(i, ts...);
				return i;
			}
		}

		assert(false);

		return InvalidEntity;
	}

	T& GetComponent(Entity entity)
	{
		AssertEntityValid(entity);

		return components[entity];
	}

	void ReleaseComponent(Entity entity)
	{
		AssertEntityValid(entity);

		allocateInfos[entity] = false;
		
		if (entity < minimumLastFreedEntity)
		{
			minimumLastFreedEntity = entity;
		}

		if (entity == lastEntity)
		{
			--lastEntity;
		}
	}

private:

	template<typename ...Ts>
	inline void AllocateAtIndex(Entity entity, const Ts&... ts)
	{
		AssertEntityValid(entity);

		components[entity] = { ts... };
		allocateInfos[entity] = true;
	}

	T components[Size];
	bool allocateInfos[Size];

	Entity minimumLastFreedEntity = Size;
	Entity lastEntity = 0;
};