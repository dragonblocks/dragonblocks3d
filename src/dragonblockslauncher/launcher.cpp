#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>
#include "dragonblockslauncher/launcher.hpp"
 
using namespace dragonblockslauncher;

void dragonblockslauncher::log(std::string message)
{
	std::cout << "[Launcher] " << message << std::endl;
}

void dragonblockslauncher::fail(std::string error, std::string details)
{
	std::cerr
		<< "Unable to launch dragonblocks: " << error << std::endl
		<< "Details: " << details << std::endl;
	abort();
}

void dragonblockslauncher::launchDragonblocks(std::string gametype)
{
	void* handle;
	std::string filename;
	std::string start_function_name;
	void (*start_function)();
	
	filename = "./libdragonblocks.so";
	
	log("Opening dynamic library at " + filename);
	
	handle = dlmopen(LM_ID_BASE, filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
	
	if (!handle)
		fail("Failed to load " + filename, dlerror());
		
	if (gametype != "server" && gametype != "client" && gametype != "mainmenu")
		fail("Trying to start dragonblocks with unknown gametype", "gameype = " + gametype);

	start_function_name = "_dragonblocks_start_" + gametype;
	
	log("Obtaining start function pointer");
	
	start_function = (void (*)())dlsym(handle, start_function_name.c_str());
	
	if (!start_function)
		fail("Failed to obtain dragonblocks start function pointer", dlerror());

	log("Launching dragonblocks");

	(*start_function)();
}
