#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t spaceCount)
{
	m_BlockCount = spaceCount;
	for (size_t i = 0; i < m_BlockCount; ++i)
	{
		m_MemoryBlockSegment[i] = (MemoryBlock*)malloc(104);
		m_MemoryBlockSegment[i]->memoryUsed = 0;
		m_MemoryBlockSegment[i]->isBusy = false;
	}
}

MemoryPool::~MemoryPool()
{
	if (!m_MemoryBlockSegment.empty())
	{
		for (size_t i = 0; i < m_BlockCount; ++i)
		{
			free(m_MemoryBlockSegment[i]);
		}
	}

	std::cout << "Deleting Memory Pool" << std::endl;
	m_MemoryBlockSegment.clear();
}

void* MemoryPool::Alloc(size_t size)
{
	try
	{
		if (m_MemoryBlockSegment.empty()) { throw 0; }

		size_t t_RequestedBytes = size;

		for (int t_MemoryBlock = 0; t_MemoryBlock < m_BlockCount; ++t_MemoryBlock)
		{
			if (m_MemoryBlockSegment[t_MemoryBlock]->isBusy == false)
			{
				if (m_MemoryBlockSegment[t_MemoryBlock] == nullptr)
				{
					std::cout << "Bad malloc call" << std::endl;
					throw std::bad_alloc();
				}

				m_MemoryBlockSegment[t_MemoryBlock]->memoryUsed += t_RequestedBytes;
				m_MemoryBlockSegment[t_MemoryBlock]->blockSize = size;
				m_MemoryBlockSegment[t_MemoryBlock]->memoryBlockIndex = t_MemoryBlock;
				m_MemoryBlockSegment[t_MemoryBlock]->isBusy = true;
				m_MemoryAllocated -= 1;
				
				return m_MemoryBlockSegment[t_MemoryBlock];
			}
		}

		std::cout << "No more space in Memory Pool" << std::endl;
		return nullptr;
	}
	catch (...)
	{
		std::cout << "Bad Allocation or Memory Pool has not Memory in it" << std::endl;
		std::cout << "No Space in the Memory Pool" << std::endl;
		throw std::bad_alloc();
		return nullptr;
	}
}

void MemoryPool::Free(void* memory, size_t size)
{
	if (m_MemoryBlockSegment.empty()) { return; }

	// Free the Memory from the Program
	MemoryBlock* t_MemoryBlockAddr = (MemoryBlock*)(memory);
	int t_MemBlockIndex = t_MemoryBlockAddr->memoryBlockIndex;
	int t_MemSegmentIndex = t_MemoryBlockAddr->memorySegmentIndex;
	m_MemoryAllocated += 1;

	// Free Memory
	free(m_MemoryBlockSegment[t_MemBlockIndex]);
	m_MemoryBlockSegment[t_MemBlockIndex]->isBusy = false;
}

void MemoryPool::PrintMemoryPool()
{





}
