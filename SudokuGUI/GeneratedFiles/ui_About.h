/********************************************************************************
** Form generated from reading UI file 'About.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutUI
{
public:
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *pushButton;

    void setupUi(QWidget *AboutUI)
    {
        if (AboutUI->objectName().isEmpty())
            AboutUI->setObjectName(QStringLiteral("AboutUI"));
        AboutUI->resize(413, 250);
        textEdit = new QTextEdit(AboutUI);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(20, 20, 381, 131));
        textEdit->setStyleSheet(QStringLiteral("color:black"));
        textEdit_2 = new QTextEdit(AboutUI);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setEnabled(false);
        textEdit_2->setGeometry(QRect(60, 160, 301, 41));
        textEdit_2->setStyleSheet(QStringLiteral("color:black"));
        pushButton = new QPushButton(AboutUI);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 210, 93, 28));

        retranslateUi(AboutUI);

        QMetaObject::connectSlotsByName(AboutUI);
    } // setupUi

    void retranslateUi(QWidget *AboutUI)
    {
        AboutUI->setWindowTitle(QApplication::translate("AboutUI", "About", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("AboutUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:14pt; font-weight:600;\">Made by</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:16pt;\">  15061183   Slontia</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:16pt;\">  15231177   hitaku</span></p>\n"
"<p align=\"center\" style=\" m"
                        "argin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:14pt; font-weight:600;\">Software Engineering, BUAA</span></p></body></html>", Q_NULLPTR));
        textEdit_2->setHtml(QApplication::translate("AboutUI", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:14pt; font-weight:600;\">They're very handsome!</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AboutUI", "Yes!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AboutUI: public Ui_AboutUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
