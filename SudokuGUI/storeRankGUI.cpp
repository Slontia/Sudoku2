#include "storeRankGUI.h"
#include "rank.h"
#include <qdebug.h>
#include <qmessagebox>
#define BOARD_FONT QFont("Times", 10, QFont::Bold)
#define BOARD_STYLE "QTextEdit{\
		color:#000000;\
	}"


StoreRankGUI::StoreRankGUI(Rank* rank, QWidget *parent)
	: QWidget(parent) {
	//ui.setupUi(this);
	setEnabled(true);
	resize(388, 438);
	setFixedSize(388, 438);

	QLineEdit* text = new QLineEdit(this);
	text->setGeometry(QRect(20, 20, 200, 30));
	text->setText("Congratulations! You did a good job! Please enter your name:\n");
	text->setEnabled(false);

	input_edit = new QLineEdit();
	input_edit->setGeometry(QRect(20, 100, 200, 30));

	submit_btn = new QPushButton("Submit");
	input_edit->setGeometry(QRect(20, 150, 100, 50));
	
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
	char* name_c;
	QByteArray ba = name.toLatin1();
	name_c = ba.data();

	int time_int = time2int(time);
	rank->record(mode, (double)time_int, name_c);
	
}

