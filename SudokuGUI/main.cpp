/* WARNING:
1. Timer may overflow (after 24h)
2. Track and clean
*/

/* FUNCS:
1. check
2. tip
3. track (digit)
4. immediately checking (bool)
*/

/* MENU
1. new
2. help
3. about (Easter eggs?)
4. ranking list
*/

#include "SudokuGUI.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QFileInfo>
#include <time.h>
#include "core.h"
#include <qdebug.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SudokuGUI ui;

	int sudoku[81] = { 0 };
	int puzzle[81] = { 0 };
	FILE* fsudoku;
	FILE* fpuzzle;
	fopen_s(&fsudoku, "solution_55.txt", "w");
	fopen_s(&fpuzzle, "puzzle_55.txt", "w");

	srand((int)time(0));



	int result[1][SIZE * SIZE];
	Core core;
	//core.generate(1, 1, result);
	core.generate(1, 55, 55, true, result);
	core.solve(result[0], sudoku);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			qDebug() << sudoku[i * 9 + j];
		}
		qDebug() << endl;
	}


	//ui.new_game(0); // new game
	ui.show();
	return a.exec();
}
