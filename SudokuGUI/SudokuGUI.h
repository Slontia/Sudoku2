#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SudokuGUI.h"
#include <qpushbutton.h>
#include <QSignalMapper>
#include <QMessageBox>
#include <QLineEdit>
#include <QLCDNumber>
#include <iostream>
#include "core.h"
#include "rank.h"
#include "storeRankGUI.h"

#define SIZE 9
#define BOX_SIZE 50

/* STYLE */
#define FUNCTION_FONT QFont("Consolas", 16, QFont::Normal)
#define REMAINING_FONT QFont("Consolas", 14, QFont::Normal)
#define GRID_FONT QFont("Consolas", 18, QFont::Normal)
#define UNCERTAIN_GRID_STYLE "QPushButton:hover{\
	background-color:#AFEEEE;\
}"\
"QPushButton{\
	background-color:#66CCFF;\
}"
#define CERTAIN_GRID_STYLE "QPushButton{\
	color:#1C2460;\
	background-color:#99CCFF;\
}"
#define TIP_GRID_STYLE "QPushButton{\
	color:#1E90FF;\
	background-color:#99CCFF;\
}"
#define WRONG_GRID_STYLE "QPushButton{\
	background-color:#DC143C;\
}"
#define MARK_GRID_STYLE "QPushButton{\
	background-color:#DC143C;\
}"
#define CURRENT_GRID_STYLE "QPushButton{\
	background-color:#FFFF66;\
}"
#define INPUT_BOTTON_STYLE "QPushButton{\
	background-color:#FF69B4;\
}"
#define FUNCTION_BUTTON_STYLE "QPushButton{\
	color:#000000;\
	background-color:#FFFF66;\
}"
#define ENABLE_BUTTON_STYLE "QPushButton{\
	background-color:#DC143C;\
}"
#define DISABLE_INPUT_BUTTON_STYLE "QPushButton{\
	background-color:#FFE4E1;\
}"
#define DISABLE_FUNCTION_STYLE "QPushButton{\
	background-color:#fcf8ab;\
}"
#define WINDOW_SYTLE ""

#define EASY_BEST_FILE "ranking/easy.txt"
#define NORMAL_FILE "ranking/normal.txt"
#define DIFFICULT_FILE "ranking/difficult.txt"
#define INPUTS_COUNT SIZE + 1
#define FUNCTIONS_COUNT 4
#define CHECK 0
#define FILTER 1
#define TIP 2
#define TRACK 3
#define CLEAN 0
#define RESTORE_GRID_STYLE(btn) ((btn)->setStyleSheet((btn)->isEnabled() ? \
UNCERTAIN_GRID_STYLE : CERTAIN_GRID_STYLE))

#define GET_GRIDNO(i, j) (i * SIZE + j)
#define GET_ROWNO(gridno) (gridno / SIZE)
#define GET_COLNO(gridno) (gridno % SIZE)
#define GET_BLOCKNO(i, j) ((i / 3) * 3 + j / 3)
#define GO_THROUGH_BLOCKS(blockno) for (int i = ((blockno) / 3)*3; i < ((blockno) / 3) * 3 + 3; i++) \
for (int j = ((blockno) % 3) * 3; j < ((blockno) % 3) * 3 + 3; j++)

using namespace std;

class Timer;
class BoardGUI;
class AboutGUI;
class HelpGUI;

class SudokuGUI : public QMainWindow
{
	Q_OBJECT

public:
	SudokuGUI(QWidget *parent = Q_NULLPTR);

	void new_game(int difficulty);
	void closeEvent(QCloseEvent* event);

private:
	Ui::SudokuGUIClass ui;
	BoardGUI* board = NULL;
	StoreRankGUI* store_rank = NULL;
	AboutGUI* about = NULL;
	HelpGUI* help = NULL;

	int cur_rowno = -1;
	int cur_colno = -1;
	QPushButton* curbtn = NULL;	// -- grid to fill
	QPushButton* buttons[SIZE][SIZE];	// -- grids
	QPushButton* input_buttons[INPUTS_COUNT];	// -- input buttons from 1 to 9
	QPushButton* func_buttons[FUNCTIONS_COUNT]; // -- function buttons
	QLineEdit* grid_count = NULL;

	Timer* timer = NULL;		// -- timer
	int numbers[SIZE][SIZE];	// -- the digit of grids
	int tipped[SIZE][SIZE];
	bool checking = false;		// -- red grids exists
	bool tracking = false;		// -- is tracking numbers?
	int difficulty = 0;			// -- difficuly
	int unfilled_grid_count = -1;		// -- the number of the unfilling grids
	int sudoku[SIZE * SIZE];	// -- the final sudoku
	int puzzle[SIZE * SIZE]; // -- puzzle
	int mode = 0;
	bool tipped_bool = false;

	Core* core = NULL;

	void create_grids();
	void create_input_buttons();
	void create_func_buttons();
	void cancel_checking();
	void cancel_tracking();
	void binding_actions();
	void set_number(int i);
	void track_number(int i);
	void restore_grids_style();
	void disable_buttons();
	void enable_buttons();
	void show_store_rank();

protected:
	
	

public slots:
	void record_button(int gridno);
	void handle_number(int i);
	bool judge();
	void new_puzzle(int difficulty);
	void set_tracking();
	void filter();
	void tip();
	void show_board();
	void show_about();
	void show_help();
};