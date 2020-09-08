#include <set>
#include "mesh_gen_mgr.hpp"
#include "window.hpp"

using namespace std;
using namespace dragonblocks;

void MeshGenMgr::MeshGenerator::updateMesh()
{
}

void MeshGenMgr::addTask(MeshGenMgr::MeshGenerator *gen)
{
	queued_jobs.push(gen);
}

void MeshGenMgr::step()
{
	if (! runJob()) {
		generateJobList();
	}
}

void MeshGenMgr::run()
{
	while (true) {
		step();
	}
}

void MeshGenMgr::generateJobList()
{
	set<MeshGenMgr::MeshGenerator *> active_jobs_set;
	while (! queued_jobs.empty()) {
		MeshGenMgr::MeshGenerator *gen = queued_jobs.front();
		queued_jobs.pop();
		if (active_jobs_set.find(gen) == active_jobs_set.end()) {
			active_jobs_set.insert(gen);
			active_jobs.push(gen);
		}
	}
}


bool MeshGenMgr::runJob()
{
	if (active_jobs.empty())
		return false;
	MeshGenMgr::MeshGenerator *gen = active_jobs.front();
	active_jobs.pop();
	if (gen) {
		gen->updateMesh();
	}
	return true;
}

void MeshGenMgr::start()
{
	mesh_gen_thread = thread(&MeshGenMgr::run, this);
}
