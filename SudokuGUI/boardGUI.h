#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_Board.h"
#include <QTextEdit>
#include <QScrollArea>
#include <QLabel>
#define BOARD_COUNT_MAX 10
#define MODE_COUNT 3
#define NAMESIZE 20

using namespace std;

class Rank;

class BoardGUI : public QWidget
{
	Q_OBJECT

public:
	BoardGUI(QWidget *parent = Q_NULLPTR);
	void init_board();
	void change_tab(int mode);

private:
	char* names[MODE_COUNT][BOARD_COUNT_MAX];
	double times[MODE_COUNT][BOARD_COUNT_MAX];
	int lengths[MODE_COUNT] = { 0 };

	QTabWidget* tabWidget;
	QWidget* boards[MODE_COUNT];
	QTextEdit* texts[MODE_COUNT];

	void show_board();

public slots:
	void clear_board();
	void enter();
};