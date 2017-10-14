#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Board.h"
#include <QLineEdit>
#include <qpushbutton>
#include <QTime>

using namespace std;

class Rank;

class StoreRankGUI : public QWidget
{
	Q_OBJECT

public:
	StoreRankGUI(Rank* rank, QWidget *parent = Q_NULLPTR);
	void set_informations(int mode, QTime* time);
	static int time2int(QTime* time);

private:
	QLineEdit* input_edit = NULL;
	Rank* rank = NULL;
	QPushButton* submit_btn = NULL;
	int mode = 0;
	QTime* time = NULL;

public slots:
	void submit();
	
};