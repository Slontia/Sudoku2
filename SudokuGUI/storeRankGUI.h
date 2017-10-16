#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Board.h"
#include <QLineEdit>
#include <qpushbutton>
#include <QTime>

using namespace std;

class Rank;
class BoardGUI;

class StoreRankGUI : public QWidget
{
	Q_OBJECT

public:
	StoreRankGUI(BoardGUI* board, QWidget *parent = Q_NULLPTR);
	void set_informations(int mode, QTime* time);
	static int time2int(QTime* time);
	

private:
	QLineEdit* input_edit = NULL;
	QPushButton* submit_btn = NULL;
	QPushButton* cancel_btn = NULL;
	int mode = 0;
	QTime* time = NULL;
	BoardGUI* board = NULL;

public slots:
	void submit();
	void cancel();
	
};