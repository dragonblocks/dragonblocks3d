#include <iostream>
#include <set>
#include "async_mgr.hpp"

using namespace std;
using namespace dragonblocks;

void AsyncMgr::ITask::doAsyncTask()
{
}

void AsyncMgr::addTask(AsyncMgr::ITask *t)
{
	mtx.lock();
	queued_jobs.push_back(t);
	mtx.unlock();
}

void AsyncMgr::run()
{
	while (true) {
		set<AsyncMgr::ITask *> active_set;
		mtx.lock();
		vector<AsyncMgr::ITask *> active = queued_jobs;
		queued_jobs.clear();
		mtx.unlock();
		for (auto it = active.begin(); it != active.end(); it++) {
			AsyncMgr::ITask *t = *it;
			if (active_set.find(t) == active_set.end()) {
				t->doAsyncTask();
			}
		}
	}
}



void AsyncMgr::start()
{
	async_thread = thread(&AsyncMgr::run, this);
}
