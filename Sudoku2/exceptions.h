#pragma once
#include <iostream>
#define DEFAULT_INFO "(null)"

using namespace std;


class Exception {
private:
	string info;
public:
	Exception(string info = DEFAULT_INFO) {
		this->info = "Error: " + info;
	}

	string get_info() {
		return info;
	}
};

class InvalidCommandException : public Exception {
public :
	InvalidCommandException(string info = DEFAULT_INFO) : Exception(info) {};
};

class CannotOpenFileException : public Exception {
public:
	CannotOpenFileException(string info = DEFAULT_INFO) : Exception(info) {};
};

class BadFileException : public Exception {
public:
	BadFileException(string info = DEFAULT_INFO) : Exception(info) {};
};


