#include "DllLoader.hpp"

_CALCULATOR_UTILS_BEGIN

DllLoader::DllLoader(const char* dllPath) {
	open(dllPath);
}

DllLoader::~DllLoader() {
	close();
}

DllLoader& DllLoader::open(const char* dllPath) {

	// if the library is already opened, close it first
	if (!hModule) {
#ifdef _WIN32 // for windows
		FreeLibrary(hModule);
#else // for rest
#endif // _WIN32
	}

#ifdef _WIN32 // for windows

	hModule = LoadLibraryA(dllPath);

#else // for rest
#endif // _WIN32

	return *this;

}

DllLoader& DllLoader::close() {

	// if the file didn't open, return self
	if (hModule == nullptr) {
		return *this;
	}

#ifdef _WIN32 // for windows
	FreeLibrary(hModule);
	hModule = nullptr;
#else // for rest
#endif // _WIN32

	return *this;
}


_CALCULATOR_UTILS_END