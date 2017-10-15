#include "aboutGUI.h"

AboutGUI::AboutGUI(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(close()));
	
}