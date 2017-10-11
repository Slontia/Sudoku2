// Sudoku2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <string>
#include <regex>
#include "iostream"

#define UNKNOWN (-1)
#define CREATE 0
#define SOLVE 1
#define PUZZLE 2

#define PUZZLE_DIFFICULTY 0
#define PUZZLE_NUMBER 1

#define CREATE_SIGN "-c"
#define SOLVE_SIGN "-s"
#define PUZZLE_SIGN "-n"
#define PUZZLE_DIFFICULTY_SIGN "-m"
#define PUZZLE_NUMBER_SIGN "-r"
#define PUZZLE_NUMBER_UNIQUE_SIGN "-u"

#define LOWER_UPPER_REGEX "^0*[1-9][0-9]?~0*[1-9][0-9]?$"
#define DIFFICULTY_REGEX "^0*[1-3]$"
#define NUMBER_REGEX "^0*[1-9][0-9]{0,6}$"

#define TO_GET_SIGN 0
#define TO_GET_NUMBER 1
#define TO_GET_DIFFICULTY 2
#define TO_GET_LOWER_UPPER 3
#define TO_GET_FILENAME 4

#define SOLVE_ERROR "-s usage: '-s [filename]'"
#define CREATE_ERROR "-c usage: '-c [1-1'000'000]'"
#define PUZZLE_NUMBER_ERROR "-n -m usage: '-n [1-10'000] -r [20-55]~[20-55] [-u]'"
#define PUZZLE_DIFFICULTY_ERROR "-n -r usage: 'sudoku.exe -n [1-10'000] -m [1-3]'"
#define UNKNOWN_COMMAND_ERROR "unknown command"

using namespace std;

bool set_mode(int* cur_mode, int set_mode) {
	if (UNKNOWN == *cur_mode) {
		*cur_mode = set_mode;
		return true;
	}
	else {
		cout << "Multiple or repeated modes!" << endl;
		return false;
	}
}

bool set_puzzle_mode(int* cur_puzzle_mode, int set_puzzle_mode) {
	if (UNKNOWN == *cur_puzzle_mode) {
		*cur_puzzle_mode = set_puzzle_mode;
		return true;
	}
	else {
		cout << "Multiple or repeated puzzle modes!" << endl;
		return false;
	}
}

bool areValidModes(int mode, int puzzle_mode, bool unique) {
	if (mode == UNKNOWN) {
		return false;
	}
	else if (mode != PUZZLE && (puzzle_mode != UNKNOWN || unique)) {
		return false;
	}
	else if (mode == PUZZLE && puzzle_mode == UNKNOWN) {
		return false;
	}
	else if (unique && puzzle_mode == PUZZLE_DIFFICULTY) {
		return false;
	}
	return true;
}

bool isValidNumber(int mode, int number) {
	if (mode == CREATE && number > 1'000'000) {
		return false;
	}
	else if (mode == PUZZLE && number > 10'000) {
		return false;
	}
	return true;
}


void exception_handle(int mode, int puzzle_mode, bool unique) {
	if (mode == CREATE) {
		cout << CREATE_ERROR << endl;
	}
	else if (mode == SOLVE) {
		cout << SOLVE_ERROR << endl;
	}
	else if (puzzle_mode == PUZZLE_DIFFICULTY) {
		cout << PUZZLE_DIFFICULTY_ERROR << endl;
	}
	else if (puzzle_mode == PUZZLE_NUMBER || unique) {
		cout << PUZZLE_NUMBER_ERROR << endl;
	}
	else {
		cout << UNKNOWN_COMMAND_ERROR << endl;
	}
}


int output2file(char* filename, int result[][])

int main(int argc, char* argv[]) {
	int mode = UNKNOWN;
	int puzzle_mode = UNKNOWN;
	bool unique = false;

	regex reg_lower_upper(LOWER_UPPER_REGEX);
	regex reg_difficulty(DIFFICULTY_REGEX);
	regex reg_number(NUMBER_REGEX);

	char* filename = NULL;
	int number = 0;
	int lower = 0;
	int upper = 0;
	int difficulty = 0;

	int status = TO_GET_SIGN;

	for (int i = 1; i < argc; i++) {
		if (status == TO_GET_SIGN && strcmp(argv[i], CREATE_SIGN) == 0 && set_mode(&mode, CREATE)) {
			status = TO_GET_NUMBER;
			continue;
		}
		else if (status == TO_GET_SIGN && strcmp(argv[i], SOLVE_SIGN) == 0 && set_mode(&mode, SOLVE)) {
			status = TO_GET_FILENAME;
			continue;
		}
		else if (status == TO_GET_SIGN && strcmp(argv[i], PUZZLE_SIGN) == 0 && set_mode(&mode, PUZZLE)) {
			status = TO_GET_NUMBER;
			continue;
		}
		else if (status == TO_GET_SIGN && strcmp(argv[i], PUZZLE_DIFFICULTY_SIGN) == 0 && set_puzzle_mode(&puzzle_mode, PUZZLE_DIFFICULTY)) {
			status = TO_GET_DIFFICULTY;
			continue;
		}
		else if (status == TO_GET_SIGN && strcmp(argv[i], PUZZLE_NUMBER_SIGN) == 0 && set_puzzle_mode(&puzzle_mode, PUZZLE_NUMBER)) {
			status = TO_GET_LOWER_UPPER;
			continue;
		}
		else if (status == TO_GET_SIGN && strcmp(argv[i], PUZZLE_NUMBER_UNIQUE_SIGN) == 0) {
			if (unique) {
				exception_handle(mode, puzzle_mode, unique);
				return 0;
			}
			unique = true;
			status = TO_GET_SIGN;
			continue;
		}
		else if (status == TO_GET_NUMBER && regex_match(*(new string(argv[i])), (*new smatch), reg_number)) {
			sscanf(argv[i], "%d", &number);
			status = TO_GET_SIGN;
			continue;
		}
		else if (status == TO_GET_DIFFICULTY && regex_match(*(new string(argv[i])), (*new smatch), reg_difficulty)) {
			sscanf(argv[i], "%d", &difficulty);
			status = TO_GET_SIGN;
			continue;
		}
		else if (status == TO_GET_LOWER_UPPER && regex_match(*(new string(argv[i])), (*new smatch), reg_lower_upper)) {
			sscanf(argv[i], "%d~%d", &lower, &upper);
			status = TO_GET_SIGN;
			continue;
		}
		else if (status == TO_GET_FILENAME) {
			filename = argv[i];
			status = TO_GET_SIGN;
			continue;
		}
		else {
			exception_handle(mode, puzzle_mode, unique);
			return 0;
		}
	}

	if (!areValidModes(mode, puzzle_mode, unique || 
		status != TO_GET_SIGN ||
		!isValidNumber(mode, number)
	)) {
		exception_handle(mode, puzzle_mode, unique);
		return 0;
	}

	Core core;

	switch (mode) {
	case CREATE:
		core.generate()
		break;
	case SOLVE:
		cout << "SOLVE:" << filename << endl;
		break;
	case PUZZLE:
		if (puzzle_mode == PUZZLE_DIFFICULTY) {
			cout << "PUZZLE_DIFFICULTY:" << number << " MODE:" << difficulty << endl;
		}
		else if (puzzle_mode == PUZZLE_NUMBER) {
			cout << "PUZZLE_NUMBER:" << number << " FROM:" << lower << " TO:" << upper << " " << unique << endl;
		}
		break;
	default:
		
	}
}



/*int main() {
	int sudoku[81] = { 0 };
	int puzzle[81] = { 0 };
	FILE* fsudoku;
	FILE* fpuzzle;
	fopen_s(&fsudoku, "solution_55.txt", "w");
	fopen_s(&fpuzzle, "puzzle_55.txt", "w");

	srand((int)time(0));

	

	int result[NUM][SIZE * SIZE];
	Core::generate(NUM, 55, 55, true, result);

	for (int sudoku_counter = 0; sudoku_counter < NUM; sudoku_counter++) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				//fputc(sudoku[i * 9 + j] + '0', fsudoku);
				//fputc(' ', fsudoku);
				fputc(result[sudoku_counter][i * 9 + j] + '0', fpuzzle);
				fputc(' ', fpuzzle);
			}
			//fputc('\n', fsudoku);
			fputc('\n', fpuzzle);
		}
		//fputc('\n', fsudoku);
		fputc('\n', fpuzzle);
	}

	

}*/


/*int main() {
	int result[1000][81];
	srand((int)time(0));

	double dur;
	clock_t start, end;
	start = clock();

	Core::generate(1000, 45, 45, true, result);

	end = clock();
	dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
}*/

