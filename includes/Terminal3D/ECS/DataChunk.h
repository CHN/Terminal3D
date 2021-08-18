#pragma once

#include "ECSCore.h"

#include <utility>

ECS_NAMESPACE_BEGIN

template<typename ComponentType, size_t PreAllocatedComponentCount>
struct DataChunkComponent 
{
	static constexpr ComponentType type;
	static constexpr size_t PreAllocatedComponentCount = PreAllocatedComponentCount;
	static constexpr size_t ComponentSize = sizeof(type);
};

template<size_t PreAllocatedComponentCount, typename ...ComponentTypes>
struct ArcheComponent
{
	static constexpr size_t PreAllocatedComponentCount = PreAllocatedComponentCount;
	static constexpr size_t ComponentSize = (sizeof(ComponentTypes) + ...);
};

template<typename ...DataChunkComponents>
class DataChunk
{
public:

	DataChunk()
	{
		DataChunkParser<DataChunkComponents...>();
	}

	~DataChunk()
	{
		delete[] chunk;
	}

	size_t GetTotalSize()
	{
		return totalSize;
	}

private:

	template<typename none = void, std::enable_if_t<std::is_same_v<none, void>, bool> = true>
	void DataChunkParser()
	{

	}

	template<typename FirstDataChunkComponent, typename ...DataChunkComponents>
	void DataChunkParser()
	{
		totalSize += FirstDataChunkComponent::PreAllocatedComponentCount * FirstDataChunkComponent::ComponentSize;

		DataChunkParser<DataChunkComponents...>();
	}

	char* chunk = nullptr;
	size_t totalSize = 0;
};

ECS_NAMESPACE_END