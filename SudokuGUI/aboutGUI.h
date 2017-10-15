#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_About.h"

using namespace std;

class Rank;

class AboutGUI : public QWidget
{
	Q_OBJECT

public:
	AboutGUI(QWidget *parent = Q_NULLPTR);
	Ui::AboutUI ui;
	
private:
	
};