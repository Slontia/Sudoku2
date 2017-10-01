#include "stdafx.h"
#define EXCHANGER_GROUPS_SIZE 3		// -- 对几个数字进行全排列
#define EXCHANGER_GROUPS_COUNT 3	// -- 有几组数字需要排列
#define MAX_EXCHANGE_COUNT 6		// -- 一共需要交换几次
#define EXCHANGER_COUNT 12			// -- 共有几个Exchanger

class Exchanger {
private:
	int exchange_counter = 0;	// -- record exchanging times
	bool mode = true;			// -- exchange (1, 2) when true; overwise exchange (2, 3)
	char *c1, *c2;				// -- char to exchange

public:
	Exchanger* next = NULL;		// -- the pointer of next exchanger
	char* perms[EXCHANGER_GROUPS_COUNT][EXCHANGER_GROUPS_SIZE];	// -- numbers to permutate

	Exchanger() {}

	void exchange() 
	{
		for (int i = 0; i < EXCHANGER_GROUPS_COUNT; i++) 
		{
			// choose char
			if (mode) 
			{
				c1 = perms[i][0];
				c2 = perms[i][1];
			}
			else 
			{
				c1 = perms[i][1];
				c2 = perms[i][2];
			}
			// exchange
			*c1 = (*c1) ^ (*c2);
			*c2 = (*c1) ^ (*c2);
			*c1 = (*c1) ^ (*c2);
		}
	}

	void try_activate_next() 
	{
		exchange_counter++;			// -- count exchanging
		if (exchange_counter == MAX_EXCHANGE_COUNT) 
		{
			exchange_counter = 0;	// -- initial counter
			if (next != NULL) 
			{
				next->change2next();
			}
		}
	}

	void change2next() 
	{
		exchange();				// -- change the char
		try_activate_next();	// -- activate next exchanger if gone through all permutations
	}
};

void initial_sudoku(int sudoku[SIZE][SIZE])
{

}

void initial_exchanger(Exchanger* exchangers[]) 
{

}

void output_sudoku(int sudoku[SIZE][SIZE], int result[SIZE*SIZE]) 
{

}

void create_sudokus(int number, int result[][SIZE*SIZE]) 
{
	int sudoku[SIZE][SIZE];
	Exchanger* exchangers[EXCHANGER_COUNT];
	/* initial */
	initial_sudoku(sudoku);
	initial_exchanger(exchangers);
	/* create */
	Exchanger* head_exchanger = exchangers[0];
	for (int count = 0; count < number; count++)	// (for each result)
	{	
		output_sudoku(sudoku, result[count]);	// -- write to result[][]
		head_exchanger->change2next();			// -- change the sudoku
	}
}


/*void create_sudokus(int number, int result[][SIZE*SIZE]) {
	Template_sudoku templ = Template_sudoku();
	//vector<vector<int>>* sudokus = new vector<vector<int>>(number);
	//sudokus.resize(number);
	
	for (int count = 0; count < number; count++) {
		//vector<int> & sudoku = sudokus[count];
		//vector<int> sudoku(sudokus->at(count));
		//sudoku.reserve(BOX_COUNT);
		templ.create_from_template(result[count]);
		templ.change2next();
	}
}*/