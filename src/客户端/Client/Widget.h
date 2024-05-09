#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ConnectBtn_clicked();

    void on_sendBtn_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;//网络通信对象
};
#endif // WIDGET_H
