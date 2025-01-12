#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "Constants.h"
#include "Structures.h"

class ThreadPool
{
private:

	std::vector<std::thread> m_Threads;

	std::queue<function<void()>> m_Tasks;

	std::mutex m_Mut;

	condition_variable m_MainConVar;
	condition_variable m_CustomConVar;

	int m_RunningProcesses = 0;
	bool m_Stop = false;

public:
	
	// CLASS FUNCTION(s)
	ThreadPool(size_t numberOfThreads);
	~ThreadPool();

	// BASE FUNCTION(s)
	void Enqueue(function<void()> task);
	void JoinThreads();

	void WaitTasksDone();

	// GETTER FUNCTION(s)
	inline bool GetStop() const { return m_Stop; }
	inline float ThreadSize() { return m_Threads.size(); }

	inline int GetRunningProcess() const { return m_RunningProcesses; }
	inline bool GetTaskListIsEmpty() const { return m_Tasks.empty(); }
};

#endif