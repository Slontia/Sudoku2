#pragma once
#include "stdafx.h"

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
#define CREATE_ERROR "-c usage: '-c [number(1-1'000'000)]'"
#define PUZZLE_NUMBER_ERROR "-n -m usage: '-n [number(1-10'000)] -r [lower(20-55)]~[upper(20-55)] [-u]'\n(lower <= upper)"
#define PUZZLE_DIFFICULTY_ERROR "-n -r usage: 'sudoku.exe -n [number(1-10'000)] -m [mode(1-3)]'"
#define UNKNOWN_COMMAND_ERROR "Unknown command!"
#define FILE_ERROR "Cannot open the file! Please check the path."

//#define BUFFER_SIZE 1'000
#define CREATE_NUMBER_MAX 1'000'000
#define PUZZLE_NUMBER_MAX 10'000
#define LOWER_MIN 20
#define UPPER_MAX 55

#define OUTPUT_FILENAME "sudoku.txt"


bool set_mode(int* cur_mode, int set_mode);

bool set_puzzle_mode(int* cur_puzzle_mode, int set_puzzle_mode);

bool areValidModes(int mode, int puzzle_mode, bool unique);

bool isValidNumber(int mode, int puzzle_mode, int number, int lower, int upper);

void exception_handle(int mode, int puzzle_mode, bool unique);

int read_command(int argc, char* argv[]);