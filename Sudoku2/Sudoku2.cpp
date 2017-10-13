// Sudoku2.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "iostream"

int main(int argc, char* argv[]) {
	try {
		read_command(argc, argv);
	}
	catch (Exception* e) {
		cout << e->get_info() << endl;
	}
}