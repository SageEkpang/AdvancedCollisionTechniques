#pragma once
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "Structures.h"
#include "Constants.h"

struct MemoryBlock
{
	int memoryUsed;
	int memorySegmentIndex;
	int memoryBlockIndex;
	int blockSize;
	bool isBusy;
};

class MemoryPool
{
private:

	// TODO: CHANGE TO 2 VECTOR, ONE FOR FREE SPACE AND ONE FOR NOT FREE SPACE

	std::vector<MemoryBlock*> m_MemoryBlockSegment;
	int m_BlockCount;
	int m_MemoryAllocated;

public:

	MemoryPool* m_MemoryPool;

	// CLASS FUNCTION(s)
	MemoryPool(size_t spaceCount);
	~MemoryPool();

	// BASE FUNCTION(s)
	void* Alloc(size_t size);
	void Free(void* memory, size_t size);


	// GETTER FUNCTION(s)
	void PrintMemoryPool();


	// SETER FUNCTION(s)
	inline int GetMemoryAllocated() const { return m_MemoryAllocated; }


};

#endif