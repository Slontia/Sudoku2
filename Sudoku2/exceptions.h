#pragma once
#include <iostream>
using namespace std;

class Exception {
private:
	string info;
public:


	string get_info() {
		return info;
	}
};

class InvalidCommandException : public Exception {

};
