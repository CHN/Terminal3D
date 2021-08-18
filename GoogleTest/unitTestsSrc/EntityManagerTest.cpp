#include "../../includes/Terminal3D/ECS/EntityManager.h"

#include "gtest/gtest.h"

#include <chrono>
#include <random>

TEST(EntityManager, SequentialAllocateReleaseTest)
{
	constexpr size_t Size = 1000;
	ECS::EntityManager em(Size);

	int prevEn = -1;

	for (size_t i = 0; i < Size; ++i)
	{
		int curEn = em.Allocate();

		ASSERT_TRUE(curEn - prevEn == 1);

		prevEn = curEn;
	}

	for (size_t i = Size - 1; i != ~0; --i)
	{
		em.Release(i);
	}

	prevEn = -1;

	for (size_t i = 0; i < Size; ++i)
	{
		int curEn = em.Allocate();

		ASSERT_TRUE(curEn - prevEn == 1);

		prevEn = curEn;
	}

	for (size_t i = Size - 1; i != ~0; --i)
	{
		em.Release(i);
	}

	prevEn = -1;

	for (size_t i = 0; i < Size; ++i)
	{
		int curEn = em.Allocate();

		ASSERT_TRUE(curEn - prevEn == 1);

		prevEn = curEn;
	}
}

TEST(EntityManager, RandomAllocateReleaseTest)
{
	std::random_device rd;
	std::mt19937::result_type seed = rd() ^ (
		(std::mt19937::result_type)
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count() +
		(std::mt19937::result_type)
		std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			).count());

	std::mt19937 gen(seed);

	constexpr size_t Size = 100;

	ECS_NS::EntityManager em(Size);
	std::vector<ECS_NS::Entity> entities;
	
	size_t testCount = gen() % 20 + 10;

	for (int x = 0; x < testCount; ++x)
	{
		size_t allocateCount = gen() % (Size - entities.size() + 1);

		while (allocateCount--)
		{
			ECS_NS::Entity e = em.Allocate();

			auto it = std::find(entities.begin(), entities.end(), e);
			ASSERT_EQ(it, entities.end());

			entities.push_back(e);
		}

		size_t releaseCount = gen() % (entities.size() + 1);

		while (releaseCount--)
		{
			ECS_NS::Entity e = gen() % entities.size();
			em.Release(entities[e]);
			entities.erase(entities.begin() + e);
		}
	}
}