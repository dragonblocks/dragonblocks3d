#include "mesh_gen_thread.hpp"

using namespace std;
using namespace dragonblocks;

void MeshGenThread::MeshGenerator::updateMesh()
{
}

void MeshGenThread::addTask(MeshGenThread::MeshGenerator *gen)
{
	queued_jobs[gen] = true;
}

void MeshGenThread::step()
{
	if (! runJob()) {
		generateJobList();
	}
}

void MeshGenThread::generateJobList()
{
	for (auto it = queued_jobs.begin(); it != queued_jobs.end(); it++) {
		active_jobs.push_back(it->first);
	}
	queued_jobs.clear();
}


bool MeshGenThread::runJob()
{
	int s = active_jobs.size();
	if (s == 0)
		return false;
	MeshGenThread::MeshGenerator *gen = active_jobs[s - 1];
	active_jobs.pop_back();
	if (gen) {
		gen->updateMesh();
	}
	return true;
}

