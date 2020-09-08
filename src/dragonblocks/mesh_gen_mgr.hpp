#pragma once

#include <thread>
#include <queue>

namespace dragonblocks
{
	class Window;
	
	class MeshGenMgr : public std::thread
	{
		public:
		class MeshGenerator
		{
			public:
			virtual void updateMesh();
		};
		
		void addTask(MeshGenerator *);
		void step();
		void run();
		void start();
				
		private:
		void generateJobList();
		bool runJob();
		
		std::queue<MeshGenerator *> queued_jobs;
		std::queue<MeshGenerator *> active_jobs;
		std::thread mesh_gen_thread;
	};
}
