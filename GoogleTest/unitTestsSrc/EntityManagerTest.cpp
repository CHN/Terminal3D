#include "../../includes/Terminal3D/EntityManager.h"

#include "gtest/gtest.h"

namespace
{
	struct DummyComponent
	{
		float a;
		int b;
		char c;
	};
}

TEST(EntityManager, MinimumLastFreedIndexTest)
{
	EntityManager<DummyComponent> em;

	Entity s = em.AddComponent();

	EXPECT_TRUE(s >= 0);

	em.ReleaseComponent(s);

	Entity s1 = em.AddComponent();

	EXPECT_EQ(s, s1);

	Entity s2 = em.AddComponent();

	em.ReleaseComponent(s1);

	Entity s3 = em.AddComponent();

	EXPECT_EQ(s, s3);

	em.ReleaseComponent(s2);

	Entity s4 = em.AddComponent();

	EXPECT_EQ(s2, s4);
}


TEST(EntityManager, AddGetVariableEqualityTest)
{
	EntityManager<DummyComponent> em;

	Entity s = em.AddComponent(1.f, 2, 'c');

	EXPECT_TRUE(s >= 0);

	auto& c1 = em.GetComponent(s);

	EXPECT_EQ(c1.a, 1.f);
	EXPECT_EQ(c1.b, 2);
	EXPECT_EQ(c1.c, 'c');

	em.ReleaseComponent(s);

	Entity s1 = em.AddComponent(3.f, 0, 'd');

	EXPECT_EQ(s, s1);

	EXPECT_EQ(c1.a, 3.f);
	EXPECT_EQ(c1.b, 0);
	EXPECT_EQ(c1.c, 'd');
}

TEST(EntityManager, ExtensiveAddRemoveTest)
{
	constexpr size_t Size = 1000;
	EntityManager<DummyComponent, Size> em;

	Entity prevEn = -1;

	for (size_t i = 0; i < Size; ++i)
	{
		Entity curEn = em.AddComponent();

		EXPECT_TRUE(curEn - prevEn == 1);

		prevEn = curEn;
	}

	for (size_t i = 0; i < Size; ++i)
	{
		em.ReleaseComponent(i);
	}

	prevEn = -1;

	for (size_t i = 0; i < Size; ++i)
	{
		Entity curEn = em.AddComponent();

		EXPECT_TRUE(curEn - prevEn == 1); // Fix last index and minimum index problems

		prevEn = curEn;
	}
}