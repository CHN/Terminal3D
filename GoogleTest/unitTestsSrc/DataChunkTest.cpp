#include "../../includes/Terminal3D/ECS/DataChunk.h"

#include "gtest/gtest.h"

struct Position { int a; };
struct Rotation {};
struct Scale {};

TEST(DataChunk, CompileTest)
{
	using namespace ECS_NS;

	DataChunk<
		DataChunkComponent<Position, 10>, 
		DataChunkComponent<Rotation, 25>, 
		DataChunkComponent<Scale, 35>,
		ArcheComponent<35, Position, Scale, Position>
	> dataChunk;

	EXPECT_EQ(dataChunk.GetTotalSize(), 100);
}