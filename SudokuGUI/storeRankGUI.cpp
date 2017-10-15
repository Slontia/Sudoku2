#pragma execution_character_set("utf-8")

#include "storeRankGUI.h"
#include "rank.h"
#include <qdebug.h>
#include <qmessagebox>
#include "boardGUI.h"
#include "QTextEdit"
#define BOARD_FONT QFont("Times", 10, QFont::Bold)
#define BOARD_STYLE "QTextEdit{\
		color:#000000;\
	}"


StoreRankGUI::StoreRankGUI(Rank* rank, BoardGUI* board, QWidget *parent)
	: QWidget(parent) {
	//ui.setupUi(this);
	setEnabled(true);
	setFixedSize(250, 170);
	this->rank = rank;
	this->board = board;

	QTextEdit* text = new QTextEdit(this);
	text->setGeometry(QRect(20, 20, 210, 90));
	text->setText("Congratulations! \nYou did a good job! \nPlease enter your name:\n");
	text->setStyleSheet("color:black");
	text->setEnabled(false);

	input_edit = new QLineEdit(this);
	input_edit->setGeometry(QRect(25, 80, 200, 25));
	input_edit->setEnabled(true);

	submit_btn = new QPushButton("Submit", this);
	submit_btn->setGeometry(QRect(30, 120, 80, 30));
	submit_btn->setDefault(true);
	QObject::connect(submit_btn, SIGNAL(clicked()), this, SLOT(submit()));

	cancel_btn = new QPushButton("Cancel", this);
	cancel_btn->setGeometry(QRect(130, 120, 80, 30));
	QObject::connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel()));
}

void StoreRankGUI::set_informations(int mode, QTime* time) {
	this->mode = mode;
	this->time = time;
}


int StoreRankGUI::time2int(QTime* time) {
	if (time == NULL) {
		return -1;
	}
	int time_int = 0;
	time_int += time->hour();
	time_int *= 60;
	time_int += time->minute();
	time_int *= 60;
	time_int += time->second();
	time_int *= 1000;
	time_int += time->msec();
	return time_int;
}


void StoreRankGUI::submit() {
	QString name = input_edit->text();
	if (name.length() >= NAMESIZE) {
		QMessageBox::critical(
			NULL,
			"Submit",
			"Your name is too long!"
		);
		return;
	}
	else if (name.length() == 0) {
		QMessageBox::critical(
			NULL,
			"Submit",
			"Your name cannot be empty!"
		);
		return;
	}
	char* name_c;
	QByteArray ba = name.toLatin1();
	name_c = ba.data();

	int time_int = time2int(time);

	qDebug() << (double)time_int << endl;
	qDebug() << name_c << endl;
	// this->rank->clear();
	qDebug() << "mode: " << mode << endl;
	//this->rank->record(mode, (double)time_int, name_c);
	this->rank->record(mode, (double)time_int, name_c);
	this->rank->encrypt_flush(ENCRYPT);
	
	if (this->board == NULL) {
		this->board = new BoardGUI(rank);
	}
	this->board->change_tab(mode);
	this->board->init_board();
	this->board->show();
	this->close();
}


void StoreRankGUI::cancel() {
	this->close();
}
