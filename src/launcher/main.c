#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __USE_GNU
#include <dlfcn.h>

void launch_dragonblocks(const char *gametype)
{
	void* handle;
	const char *filename;
	char *start_function_name;
	void (*start_function)();
	
	filename = "./libdragonblocks.so";
	
	printf("Opening %s\n", filename);
	
	handle = dlmopen(LM_ID_BASE, filename, RTLD_NOW | RTLD_GLOBAL);
	
	if (! handle) {
		printf("Failed to load %s\n\tDetails: %s\n", filename, dlerror());
		abort();
	}
		
	if (strcmp(gametype, "client")) { // && strcmp(gametype, "server") && strcmp(gametype, "menu")
		printf("Trying to start dragonblocks with unknown gametype (\"%s\")\n", gametype);
		abort();
	}
	
	start_function_name = malloc(strlen("_dragonblocks_start_") + strlen(gametype) + 1);
	strcpy(start_function_name, "_dragonblocks_start_");
	strcat(start_function_name, gametype);
	
	printf("Obtaing pointer to start function\n");
	
	start_function = (void (*)())dlsym(handle, start_function_name);
	
	free(start_function_name);
	
	if (! start_function) {
		printf("Failed to obtain dragonblocks start function pointer\n\tDetails: %s\n", dlerror());
		abort();
	}

	printf("Starting dragonblocks\n");

	(*start_function)();
}

int main(int argc, char *argv[])
{
	launch_dragonblocks("client");
}
