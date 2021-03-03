// Just some code to use later when C++ Runtime Mods are introduced

class DynamicLibrary
{
	public:
	std::string filename;
	std::string error;
	bool success;
	void *handle;
	DynamicLibrary(std::string);
};
DynamicLibrary *loadDynamicLibrary(std::string); 

DynamicLibrary::DynamicLibrary(std::string f)
{
	filename = f;
	
	handle = dlmopen(LM_ID_BASE, filename.c_str(), RTLD_NOW | RTLD_GLOBAL);
	
	if (handle) {
		success = true;
	} else {
		error = dlerror();
		success = false;
	}
}
