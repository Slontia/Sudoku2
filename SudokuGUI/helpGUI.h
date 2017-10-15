#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_Help.h"

using namespace std;

class Rank;

class HelpGUI : public QWidget
{
	Q_OBJECT

public:
	HelpGUI(QWidget *parent = Q_NULLPTR);
	Ui::Help ui;

private:

};