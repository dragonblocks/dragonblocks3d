#pragma once

#include <mutex>
#include <thread>
#include <vector>

namespace dragonblocks
{
	class AsyncMgr : public std::thread
	{
		public:
		class ITask
		{
			public:
			virtual void doAsyncTask();
		};
		
		void addTask(ITask *);
		void run();
		void start();
				
		private:
		std::mutex mtx;
		std::vector<ITask *> queued_jobs;
		std::thread async_thread;
	};
}
