#pragma once
#ifndef __CALCULATOR_DLLLOADER_BASIC_H
#define __CALCULATOR_DLLLOADER_BASIC_H

#include "../macros.h"

#ifdef _WIN32

#include <Windows.h>

#else // else _WIN32

// include some headers for linux or macos, that is, operating system other than windows,
// but currently, I don't know what headers to include, so I will leave it empty for now

#endif // _WIN32


_CALCULATOR_UTILS_BEGIN

// load functions from dll files
class DllLoader {
public:
	DllLoader() = default;

	// constuctor with dll file path, will open the dll file
	DllLoader(const char* dllPath);

	// destructor, will close the dll file
	~DllLoader();

	// get function pointer from dll file
	// @param functionName the name of the function to get
	template<typename FunctionType>
	FunctionType* getFunction(const char* functionName)const {

#ifdef _WIN32 // for windows

		// if the dll file is not opened, return null
		if (hModule == nullptr) {
			return nullptr;
		}
		return (FunctionType*)(GetProcAddress(hModule, functionName));

#else // for rest

		return nullptr;

#endif // _WIN32

	}

	// assignment operator are deleted to prevent copying, 'cause a file cannot opened twice
	DllLoader& operator=(const DllLoader&) = delete;

	// copy constructor are deleted to prevent copying, 'cause a file cannot opened twice, likes assignmet operator
	DllLoader(const DllLoader&) = delete;

	// open a dll file
	DllLoader& open(const char* dllPath);

	// close the dll file opening
	DllLoader& close();

#ifdef _WIN32
private:

	// the handle of the dll file
	HMODULE hModule;

#else // else _WIN32

	// the handle of the dll file, for linux or macos, that is, operating system other than windows,
	// but currently, I don't know what type to use, so I will leave it empty for now

#endif // _WIN32

}; // end class DllLoader

_CALCULATOR_UTILS_END

#endif // !__CALCULATOR_DLLLOADER_BASIC_H
