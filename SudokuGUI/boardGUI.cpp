#include "boardGUI.h"
#include "rank.h"
#include <qdebug.h>
#define BOARD_FONT QFont("Times", 10, QFont::Bold)
#define BOARD_STYLE "QTextEdit{\
		color:#000000;\
	}"


BoardGUI::BoardGUI(Rank* rank, QWidget *parent)
	: QWidget(parent) {
	//ui.setupUi(this);
	setEnabled(true);
	resize(388, 438);
	setFixedSize(388, 438);

	tabWidget = new QTabWidget(this);
	tabWidget->setObjectName(QStringLiteral("tabWidget"));
	tabWidget->setEnabled(true);
	tabWidget->setGeometry(QRect(20, 20, 350, 400));
	for (int i = 0; i < MODE_COUNT; i++) {
		boards[i] = new QWidget();
		tabWidget->addTab(boards[i], QString());
		texts[i] = new QTextEdit(boards[i]);
		texts[i]->setEnabled(false);
		texts[i]->setGeometry(QRect(0, 0, 350, 400));
		texts[i]->setStyleSheet(BOARD_STYLE);
		texts[i]->setFont(BOARD_FONT);
	}

	this->setWindowTitle(QApplication::translate("Rank", "Rank", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[EASY]), QApplication::translate("Form", "Easy", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[MID]), QApplication::translate("Form", "Normal", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[HARD]), QApplication::translate("Form", "Hard", Q_NULLPTR));
	
	
	//boards[EASY] = new QWidget();
	//boards[EASY]->setObjectName(QStringLiteral("boards[EASY]"));
	//texts[EASY] = new QTextEdit(boards[EASY]);
	//texts[EASY]->setObjectName(QStringLiteral("texts[EASY]"));
	//texts[EASY]->setEnabled(false);
	//texts[EASY]->setGeometry(QRect(0, 0, 350, 400));
	//tabWidget->addTab(boards[EASY], QString());
	/*
	boards[MID] = new QWidget();
	boards[MID]->setObjectName(QStringLiteral("boards[NORMAL]"));
	texts[MID] = new QTextEdit(boards[MID]);
	texts[MID]->setObjectName(QStringLiteral("texts[NORMAL]"));
	texts[MID]->setEnabled(false);
	texts[MID]->setGeometry(QRect(0, 0, 350, 400));
	tabWidget->addTab(boards[MID], QString());

	boards[HARD] = new QWidget();
	boards[HARD]->setObjectName(QStringLiteral("boards[HARD]"));
	texts[HARD] = new QTextEdit(boards[HARD]);
	texts[HARD]->setObjectName(QStringLiteral("texts[HARD]"));
	texts[HARD]->setEnabled(false);
	texts[HARD]->setGeometry(QRect(0, 0, 350, 400));
	tabWidget->addTab(boards[HARD], QString());

	qDebug() << 2;
	texts[EASY]->setStyleSheet(BOARD_STYLE);
	texts[EASY]->setFont(BOARD_FONT);*/

	

	//tabWidget->setCurrentIndex(0);


	//QMetaObject::connectSlotsByName(this);


	qDebug() << 3;



	//init_board();
	//ui.texts[EASY]->setText(names[0][0]);

	this->rank = rank;

	char name1[NAMESIZE];
	char name2[NAMESIZE];
	double time;
	if (rank->clear()) {
		cout << "clear error!" << endl;
	}
	rank->record(EASY, 2, "132132");
	rank->record(EASY, 3, "99999");
	rank->encrypt_flush(ENCRYPT);
	init_board();
	/*rank->fetch_rank(0, 1, name1, time);
	rank->encrypt_flush(ENCRYPT);
	rank->fetch_rank(0, 2, name2, time);
	rank->encrypt_flush(ENCRYPT);
	texts[EASY]->setText((QString)name1 + '\n' + name2);*/
	
	//ui.boards[EASY]->set
}

void BoardGUI::init_board() {
	for (int mode = 0; mode < MODE_COUNT; mode++) {
		lengths[mode] = rank->fetch_rank
			(mode, 1, BOARD_COUNT_MAX, names[mode], times[mode]);
		QString text = "";
		for (int i = 0; i < lengths[mode]; i++) {
			text += (QString)"No." + (i + '1') + "\n" + names[mode][i] + "\t";
			long time = (long)times[mode][i];
			int ms, s, min, h;
			char ms_str[10], s_str[10], min_str[10], h_str[10];
			ms = time % 1000;
			sprintf(ms_str, "%d", ms);
			time /= 1000;
			s = time % 60;
			sprintf(s_str, "%00d", s);
			time /= 60;
			min = time % 60;
			sprintf(min_str, "%00d", min);
			time /= 60;
			h = time;
			sprintf(h_str, "%000d", h);
			text += (QString)h_str + ":" + min_str + ":" + s_str + "." + ms_str + "\n";
			texts[mode]->setText(text);
		}
	}
}

void BoardGUI::show_board() {
	
}