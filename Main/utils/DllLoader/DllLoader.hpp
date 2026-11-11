#pragma once
#ifndef CALCULATOR__UTILS__DLLLOADER_H__
#define CALCULATOR__UTILS__DLLLOADER_H__

#include "../header.h"

#include <stdexcept>
#include <string>

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

	// constructor with dll file path, will open the dll file
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

		FunctionType* funcPtr = (FunctionType*)(GetProcAddress(hModule, functionName));

		if (funcPtr == nullptr) {

			// if the function is not found, throw an exception
			throw FunctionNotFoundException(dllPath, functionName);
		}

		return funcPtr;


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

 	// the handle of the dll file on windows
	HMODULE hModule = nullptr;

#else // else _WIN32

	// the handle of the dll file, for linux or macos, that is, operating system other than windows,
	// but currently, I don't know what type to use, so I will use void*

	// the handle of the dll file on linux/mac
	void* hModule = nullptr;

#endif // _WIN32

	// what's the path of the dll file that it's opening
	// if it isn't opened, dllPath will be "<UNKNOWN>"
	std::string dllPath = "<UNKNOWN>";

	// for some class of exception
public:

	// exception class for function not found
	class FunctionNotFoundException : public std::runtime_error {
	private:

		// where is the file
		std::string fileName;

		// what name is function
		std::string functionName;

	public:
		FunctionNotFoundException() = default;

		// constructor with all the attributes
		// @param fileName what file is the function in
		// @param functionName what name is function
		FunctionNotFoundException(const std::string& fileName, const std::string& functionName)
			: fileName(fileName), functionName(functionName), runtime_error("<UNKNOWN>") { }

		const char* what()const noexcept override;
	};

	// exception class for dll file cannot open
	class DllCannotOpenException : public std::runtime_error {
	private:
		// where is the file
		std::string fileName;

	public:
		DllCannotOpenException() = default;

		// constructor with fileName
		// @param fileName what file cannot be opened
		DllCannotOpenException(const std::string& fileName) : fileName(fileName), runtime_error("<UNKNOWN>") {}

		const char* what()const noexcept override;
	};

}; // end class DllLoader

_CALCULATOR_UTILS_END

#endif // !CALCULATOR__UTILS__DLLLOADER_H__
