/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *HostInfoBtn;
    QTextEdit *textEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *ListenBtn;
    QTextEdit *messageText;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *messageEdit;
    QPushButton *sendBtn;
    QPushButton *peopleBtn;
    QPushButton *GameBtn;
    QPushButton *RoundBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(885, 829);
        HostInfoBtn = new QPushButton(Widget);
        HostInfoBtn->setObjectName(QString::fromUtf8("HostInfoBtn"));
        HostInfoBtn->setGeometry(QRect(100, 10, 171, 61));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(100, 90, 591, 211));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 330, 551, 36));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        ListenBtn = new QPushButton(layoutWidget);
        ListenBtn->setObjectName(QString::fromUtf8("ListenBtn"));

        horizontalLayout->addWidget(ListenBtn);

        messageText = new QTextEdit(Widget);
        messageText->setObjectName(QString::fromUtf8("messageText"));
        messageText->setGeometry(QRect(110, 400, 591, 201));
        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(110, 630, 591, 36));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        messageEdit = new QLineEdit(layoutWidget1);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));

        horizontalLayout_2->addWidget(messageEdit);

        sendBtn = new QPushButton(layoutWidget1);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));

        horizontalLayout_2->addWidget(sendBtn);

        peopleBtn = new QPushButton(Widget);
        peopleBtn->setObjectName(QString::fromUtf8("peopleBtn"));
        peopleBtn->setGeometry(QRect(110, 700, 112, 34));
        GameBtn = new QPushButton(Widget);
        GameBtn->setObjectName(QString::fromUtf8("GameBtn"));
        GameBtn->setGeometry(QRect(250, 700, 112, 34));
        RoundBtn = new QPushButton(Widget);
        RoundBtn->setObjectName(QString::fromUtf8("RoundBtn"));
        RoundBtn->setGeometry(QRect(390, 700, 112, 34));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        HostInfoBtn->setText(QCoreApplication::translate("Widget", "\346\230\276\347\244\272\344\270\273\346\234\272\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        ListenBtn->setText(QCoreApplication::translate("Widget", "\347\233\221\345\220\254\345\256\242\346\210\267\347\253\257\350\277\236\346\216\245", nullptr));
        sendBtn->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        peopleBtn->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\344\272\272\346\225\260", nullptr));
        GameBtn->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        RoundBtn->setText(QCoreApplication::translate("Widget", "\346\243\200\346\237\245\345\233\236\345\220\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
