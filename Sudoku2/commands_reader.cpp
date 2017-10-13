#include "stdafx.h"
#include <regex>




bool set_mode(int* cur_mode, int set_mode) {
	if (UNKNOWN == *cur_mode) {
		*cur_mode = set_mode;
		return true;
	}
	else {
		return false;
	}
}

bool set_puzzle_mode(int* cur_puzzle_mode, int set_puzzle_mode) {
	if (UNKNOWN == *cur_puzzle_mode) {
		*cur_puzzle_mode = set_puzzle_mode;
		return true;
	}
	else {
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

bool isValidNumber(int mode, int puzzle_mode, int number, int lower, int upper) {
	if (mode == CREATE && number > CREATE_NUMBER_MAX) {
		return false;
	}
	else if (mode == PUZZLE && number > PUZZLE_NUMBER_MAX) {
		return false;
	}
	else if (
		puzzle_mode == PUZZLE_NUMBER &&
		(upper < lower || lower < LOWER_MIN || upper > UPPER_MAX)
		) {
		return false;
	}
	return true;
}


void exception_handle(int mode, int puzzle_mode, bool unique) {
	if (mode == CREATE) {
		throw new InvalidCommandException(CREATE_ERROR);
	}
	else if (mode == SOLVE) {
		throw new InvalidCommandException(SOLVE_ERROR);
	}
	else if (puzzle_mode == PUZZLE_DIFFICULTY) {
		throw new InvalidCommandException(PUZZLE_DIFFICULTY_ERROR);
	}
	else if (puzzle_mode == PUZZLE_NUMBER || unique) {
		throw new InvalidCommandException(PUZZLE_NUMBER_ERROR);
	}
	else {
		throw new InvalidCommandException(UNKNOWN_COMMAND_ERROR);
	}
}

int to_file_sudokus[CREATE_NUMBER_MAX][SIZE * SIZE] = { 0 };
int from_file_sudokus[CREATE_NUMBER_MAX][SIZE * SIZE] = { 0 };
int unsolvable_recorder[SOLVE_COUNT_MAX] = { 0 };

int read_command(int argc, char* argv[]) {
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

	if (!areValidModes(mode, puzzle_mode, unique) ||
		status != TO_GET_SIGN ||
		!isValidNumber(mode, puzzle_mode, number, lower, upper)
		) {
		exception_handle(mode, puzzle_mode, unique);
		return 0;
	}

	Core core;

	int to_solve_puzzle_count = 0;
	int solved_puzzle_count = 0;


	switch (mode) {
	case CREATE:
		cout << "CREATE:" << number << endl;
		core.generate(number, to_file_sudokus);
		core.output_file(OUTPUT_FILENAME, to_file_sudokus, number);
		break;
	case SOLVE:
		to_solve_puzzle_count = core.input_file(filename, from_file_sudokus);
		cout << "SOLVE:" << filename << endl;
		solved_puzzle_count =
			core.solve(from_file_sudokus, to_file_sudokus,
				to_solve_puzzle_count, unsolvable_recorder);
		cout << "UNSOLVED PUZZLE INDEX:\n";
		for (int i = 0; i < to_solve_puzzle_count - solved_puzzle_count; i++) {
			cout << unsolvable_recorder[i] << ' ';
		}
		cout << endl;
		core.output_file(OUTPUT_FILENAME, to_file_sudokus, solved_puzzle_count);
		/*cout << "Test" << endl;
		solved_puzzle_count = input_file(filename, from_file_sudokus);
		output_file(OUTPUT_FILENAME, from_file_sudokus, solved_puzzle_count);*/
		break;
	case PUZZLE:
		if (puzzle_mode == PUZZLE_DIFFICULTY) {
			core.generate(number, difficulty, to_file_sudokus);
			core.output_file(OUTPUT_FILENAME, to_file_sudokus, number);
			cout << "PUZZLE_DIFFICULTY:" << number << " MODE:" << difficulty << endl;
		}
		else if (puzzle_mode == PUZZLE_NUMBER) {
			core.generate(number, lower, upper, unique, to_file_sudokus);
			core.output_file(OUTPUT_FILENAME, to_file_sudokus, number);
			cout << "PUZZLE_NUMBER:" << number << " LOWER:" << lower <<
				" UPPER:" << upper << " " << (unique ? "UNIQUE" : "") << endl;
		}
		break;
	default:

		break;
	}
	return 0;
}