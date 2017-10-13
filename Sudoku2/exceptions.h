#pragma once
#include <iostream>
using namespace std;

class Exception {
private:
	string info;
public:
	Exception(string info);

	string get_info() {
		return info;
	}
};

class InvalidCommandException : public Exception {};

class CannotOpenFileException : public Exception {};

class InvalidParameterException : public Exception {};
