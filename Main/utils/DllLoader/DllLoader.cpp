#include "DllLoader.hpp"

_CALCULATOR_UTILS_BEGIN

DllLoader::DllLoader(const char* dllPath) {
	open(dllPath);
}

DllLoader::~DllLoader() {
	close();
}

DllLoader& DllLoader::open(const char* dllPath) {

	// check can open the dll file
	std::ifstream f(dllPath);
	
	if (!f.is_open()) {
		throw DllCannotOpenException(dllPath);
	}
	 
	f.close();

	// if the library is already opened, close it first
	close();

#ifdef _WIN32 // for windows

	hModule = LoadLibraryA(dllPath);

#else // for rest
#endif // _WIN32

	this->dllPath = dllPath;

	return *this;

}

DllLoader& DllLoader::close() {

	// if the file didn't open, return self
	if (hModule == nullptr) {

		dllPath = "<UNKNOWN>";

		return *this;
	}

#ifdef _WIN32 // for windows
	FreeLibrary(hModule);
#else // for rest
#endif // _WIN32

	hModule = nullptr;

	dllPath = "<UNKNOWN>";

	return *this;
}

const char* DllLoader::FunctionNotFoundException::what()const noexcept {
	std::string msg = "Calculator::Utils::DllLoader::FunctionNotFoundException:\n"
		"function \"" + functionName + "\" not found in file \"" + fileName + "\".";

	const char* msg_cstr = msg.c_str();

	return msg_cstr;
}

const char* DllLoader::DllCannotOpenException::what()const noexcept {
	std::string msg = "Calculator::Utils::DllLoader::DllCannotOpenException:\n"
		"dll file \"" + fileName + "\" cannot be opened.";
	const char* msg_cstr = msg.c_str();
	return msg_cstr;
}

_CALCULATOR_UTILS_END