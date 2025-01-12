#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numberOfThreads)
{
	// Creating the Worker Thread
	for (size_t i = 0; i < numberOfThreads; ++i)
	{
		m_Threads.emplace_back([this]
		{
			while (true)
			{
				function<void()> t_Task;
				{
					std:unique_lock<std::mutex> lock(m_Mut);

					m_CustomConVar.wait(lock, [this] { return !m_Tasks.empty() || m_Stop; });

					if (m_Stop && m_Tasks.empty()) { return; }

					t_Task = move(m_Tasks.front());
					m_Tasks.pop();
					++m_RunningProcesses; // New task was added some we increment task list
				}
				t_Task();
				std::unique_lock<std::mutex> lock(m_Mut);
				--m_RunningProcesses;
				m_MainConVar.notify_one();
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(m_Mut);
		m_Stop = true;
	}

	m_CustomConVar.notify_all();

	for (auto& t : m_Threads)
	{
		t.join();
	}
}

void ThreadPool::Enqueue(function<void()> task)
{
	{
		std::unique_lock<std::mutex> lock(m_Mut);
		m_Tasks.emplace(move(task));
	}

	m_CustomConVar.notify_one();
}

void ThreadPool::JoinThreads()
{
	std::unique_lock<std::mutex> lock(m_Mut);
	for (auto& t : m_Threads)
	{
		if (t.joinable())
		{
			t.join();
		}
	}
}

void ThreadPool::WaitTasksDone()
{
	std::unique_lock<std::mutex> lock(m_Mut);
	m_MainConVar.wait(lock, [this] { return m_Tasks.empty() && m_RunningProcesses == 0; });
}
