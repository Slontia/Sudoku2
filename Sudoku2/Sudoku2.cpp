// Sudoku2.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <time.h>

int main(int argc, char* argv[]) {
	double dur;
	clock_t start, end;
	start = clock();

	try {
		read_command(argc, argv);
	}
	catch (Exception* e) {
		cout << e->get_info() << endl;
	}

	end = clock();
	dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
}