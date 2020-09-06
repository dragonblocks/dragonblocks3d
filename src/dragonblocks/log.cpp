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
		case Gametype::SERVER:
		gt = "Server";
		break;
		case Gametype::MAINMENU:
		gt = "Mainmenu";
		break;
	}
	cout << "[" << gt << "] " << l << endl;
}
