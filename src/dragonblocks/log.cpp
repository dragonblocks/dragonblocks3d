#include <iostream>
#include "core.hpp" 
#include "log.hpp" 

using namespace std;
using namespace dragonblocks;

void dragonblocks::log(const string &l)
{
	string gt;
	switch (gametype) {
		case Gametype::CLIENT:
		gt = "Client";
		break;
	}
	cout << "[" << gt << "] " << l << endl;
}
