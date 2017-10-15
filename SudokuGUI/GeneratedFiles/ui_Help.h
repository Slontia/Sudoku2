/********************************************************************************
** Form generated from reading UI file 'Help.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QStringLiteral("Help"));
        Help->resize(861, 584);
        textEdit = new QTextEdit(Help);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(10, 10, 841, 561));
        textEdit->setStyleSheet(QStringLiteral("color:black"));
        pushButton = new QPushButton(Help);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(390, 530, 93, 28));

        retranslateUi(Help);

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QWidget *Help)
    {
        Help->setWindowTitle(QApplication::translate("Help", "Form", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("Help", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Sudoku</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-style:italic;\">Sudoku</span><span style=\" font-size:12pt;\"> is a worldwide prevailing puzzle game.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">The objective is to fill a 9\303\2279 grid with digits"
                        " so that each column, each row, and each of the nine 3\303\2273 subgrids that compose the grid contains all of the digits from 1 to 9.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To start a new game, click Game at the top of the window, click New Game and select a mode from Easy, Normal and Hard.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">During the play, to fill in digits, click empty blue buttons on the left, which will be marked by yellow, to select a cell, and click fuchsin buttons with digits on the right.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-"
                        "right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To erase your answers, select a digit and click </span><span style=\" font-size:12pt; font-weight:600;\">Erase</span><span style=\" font-size:12pt;\">.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To check or submit your current answer, click </span><span style=\" font-size:12pt; font-weight:600;\">Check</span><span style=\" font-size:12pt;\">.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To locate cells of a specific number, click a digit on the right and click </span><span style=\" font-size:12pt; font-weight:600;\">Track</span><span style=\" font-size:12pt;\">.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-i"
                        "ndent:0px;\"><span style=\" font-size:12pt;\">To see the answer of a cell, select it and click </span><span style=\" font-size:12pt; font-weight:600;\">Tip</span><span style=\" font-size:12pt;\">. The result of the current game will not be admitted to the </span><span style=\" font-size:12pt; font-style:italic;\">leaderboard</span><span style=\" font-size:12pt;\"> if you have used any tips.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To filter possibilities of a cell, select it and click </span><span style=\" font-size:12pt; font-weight:600;\">Filter</span><span style=\" font-size:12pt;\">, which returns a possible solution for the cell at each click.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To see the leaderboard, click </span><span style=\" font-size:12pt; fon"
                        "t-weight:600;\">Game</span><span style=\" font-size:12pt;\"> and click </span><span style=\" font-size:12pt; font-weight:600;\">Leaderboard</span><span style=\" font-size:12pt;\">.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To learn more about our work and us, click </span><span style=\" font-size:12pt; font-weight:600;\">About</span><span style=\" font-size:12pt;\">. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Thanks for your playing! Have a good time!</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Help", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
