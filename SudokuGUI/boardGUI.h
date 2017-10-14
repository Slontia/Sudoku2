#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Board.h"
#include <QTextEdit>
#define BOARD_COUNT_MAX 10
#define MODE_COUNT 3
#define NAMESIZE 20

using namespace std;

class Rank;

class BoardGUI : public QWidget
{
	Q_OBJECT

public:
	BoardGUI(Rank* rank, QWidget *parent = Q_NULLPTR);


private:
	char* names[MODE_COUNT][BOARD_COUNT_MAX];
	double times[MODE_COUNT][BOARD_COUNT_MAX];
	int lengths[MODE_COUNT] = { 0 };
	Rank* rank = NULL;

	QTabWidget* tabWidget;
	QWidget* boards[MODE_COUNT];
	QTextEdit* texts[MODE_COUNT];

	void init_board();
	void show_board();
};