#ifdef CALCULATOR_DEBUG

#include "pch.h"
#include "utils/DllLoader/DllLoader.hpp"
using namespace std;
using Calculator::utils::DllLoader;

int main(int argc, const char* argv[]) {

	DllLoader hello("./hello.dll");

	auto func = hello.getFunction<int(std::string)>("printByCpp");

	try {
		cout << func(std::string("printed by cpp")) << endl;
	}
	catch (const DllLoader::DllCannotOpenException& e) {
		cout << e.what() << endl;
	}
	catch (const DllLoader::FunctionNotFoundException& e) {
		cout << e.what() << endl;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	system("pause");

	return 0;
}

#endif // CALCULATOR_DEBUG
