#pragma once

#include <map>
#include <vector>

namespace dragonblocks
{
	class MeshGenThread 												// TODO: extend std::thread or something
	{
		public:
		class MeshGenerator
		{
			public:
			virtual void updateMesh();
		};
		
		void addTask(MeshGenerator *);
		void step();
		
		private:		
		void generateJobList();
		bool runJob();
		
		std::map<MeshGenerator *, bool> queued_jobs;					// This sucks i should use std::queue instead but i need to somehow make sure that a task isnt in there twice
		std::vector<MeshGenerator *> active_jobs;
		
	};
}
