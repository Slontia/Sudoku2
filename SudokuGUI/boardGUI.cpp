#include "boardGUI.h"
#include "rank.h"
#include <qdebug.h>
#include "difficulty.h"
#include <QPushButton>
#include <QMessageBox>
#define BOARD_FONT QFont("Consolas", 9)
#define BOARD_STYLE "QTextEdit{\
		color:#000000;\
	}"

#define EASY_INDEX 0
#define NORMAL_INDEX 1
#define HARD_INDEX 2

BoardGUI::BoardGUI(Rank* rank, QWidget *parent)
	: QWidget(parent) {
	//ui.setupUi(this);
	setEnabled(true);
	resize(388, 438);
	setFixedSize(388, 480);

	tabWidget = new QTabWidget(this);
	tabWidget->setObjectName(QStringLiteral("tabWidget"));
	tabWidget->setEnabled(true);
	tabWidget->setGeometry(QRect(20, 20, 350, 440));
	for (int i = 0; i < MODE_COUNT; i++) {
		boards[i] = new QWidget(tabWidget);
		tabWidget->addTab(boards[i], QString());
		texts[i] = new QTextEdit(boards[i]);
		texts[i]->setEnabled(false);
		texts[i]->setGeometry(QRect(0, 0, 350, 440));
		texts[i]->setStyleSheet(BOARD_STYLE);
		texts[i]->setFont(BOARD_FONT);
	}

	this->setWindowTitle(QApplication::translate("Rank", "Rank", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[EASY_INDEX]), QApplication::translate("Form", "Easy", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[NORMAL_INDEX]), QApplication::translate("Form", "Normal", Q_NULLPTR));
	tabWidget->setTabText(tabWidget->indexOf(boards[HARD_INDEX]), QApplication::translate("Form", "Hard", Q_NULLPTR));

	QPushButton* clear_btn = new QPushButton("Clear", this);
	clear_btn->setGeometry(QRect(190, 420, 80, 30));
	QObject::connect(clear_btn, SIGNAL(clicked()), this, SLOT(clear_board()));
	
	QPushButton* enter = new QPushButton("Enter", this);
	enter->setGeometry(QRect(280, 420, 80, 30));
	enter->setDefault(true);
	QObject::connect(enter, SIGNAL(clicked()), this, SLOT(enter()));

	this->rank = rank;
	init_board();
}

void BoardGUI::init_board() {
	for (int mode = 0; mode < MODE_COUNT; mode++) {
		lengths[mode] = rank->fetch_rank
			(mode, 1, BOARD_COUNT_MAX, names[mode], times[mode]);
		QString text = "";
		for (int i = 0; i < lengths[mode]; i++) {
			char rank_num[3];
			sprintf(rank_num, "%d", i + 1);
			text += (QString)"-- No." + rank_num + " --\n" + names[mode][i] + "\t";
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
		}
		texts[mode]->setText(text);
	}
}

void BoardGUI::show_board() {
	
}

void BoardGUI::change_tab(int mode) {
	this->tabWidget->setCurrentIndex(mode);
}

void BoardGUI::clear_board() {
	if (QMessageBox::Yes == QMessageBox::question(
		this,
		"Rank Clear",
		"Are you sure to clear the rank?",
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No
	)) {
		this->rank->clear();
		init_board();
	}
}

void BoardGUI::enter() {
	this->close();
}