/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *ConnectBtn;
    QTextEdit *textShow;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *IPEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *PortEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *messageEdit;
    QPushButton *sendBtn;
    QPushButton *nowBtn;
    QPushButton *getLoseBtn;
    QPushButton *getReallyBtn;
    QPushButton *noReallyBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1445, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ConnectBtn = new QPushButton(centralwidget);
        ConnectBtn->setObjectName(QString::fromUtf8("ConnectBtn"));
        ConnectBtn->setGeometry(QRect(1280, 80, 112, 34));
        textShow = new QTextEdit(centralwidget);
        textShow->setObjectName(QString::fromUtf8("textShow"));
        textShow->setGeometry(QRect(900, 270, 511, 341));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(900, 40, 361, 71));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        IPEdit = new QLineEdit(layoutWidget);
        IPEdit->setObjectName(QString::fromUtf8("IPEdit"));

        horizontalLayout->addWidget(IPEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        PortEdit = new QLineEdit(layoutWidget);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));

        horizontalLayout_2->addWidget(PortEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(900, 170, 501, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        messageEdit = new QLineEdit(layoutWidget1);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));

        horizontalLayout_3->addWidget(messageEdit);

        sendBtn = new QPushButton(layoutWidget1);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));

        horizontalLayout_3->addWidget(sendBtn);

        nowBtn = new QPushButton(centralwidget);
        nowBtn->setObjectName(QString::fromUtf8("nowBtn"));
        nowBtn->setGeometry(QRect(900, 640, 112, 34));
        getLoseBtn = new QPushButton(centralwidget);
        getLoseBtn->setObjectName(QString::fromUtf8("getLoseBtn"));
        getLoseBtn->setGeometry(QRect(900, 690, 112, 34));
        getReallyBtn = new QPushButton(centralwidget);
        getReallyBtn->setObjectName(QString::fromUtf8("getReallyBtn"));
        getReallyBtn->setGeometry(QRect(1040, 690, 112, 34));
        noReallyBtn = new QPushButton(centralwidget);
        noReallyBtn->setObjectName(QString::fromUtf8("noReallyBtn"));
        noReallyBtn->setGeometry(QRect(1170, 690, 112, 34));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1445, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ConnectBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP\345\234\260\345\235\200\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        sendBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        nowBtn->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\237\245\347\212\266\346\200\201", nullptr));
        getLoseBtn->setText(QCoreApplication::translate("MainWindow", "\350\256\244\350\276\223", nullptr));
        getReallyBtn->setText(QCoreApplication::translate("MainWindow", "\345\207\206\345\244\207", nullptr));
        noReallyBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\345\207\206\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
