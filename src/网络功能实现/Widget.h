#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
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
    void on_HostInfoBtn_clicked();

    void on_ListenBtn_clicked();

private:
    Ui::Widget *ui;

    QTcpServer *mServer;
    QTcpSocket *mSocket;//通信套接字
    int mPort;//端口号
};
#endif // WIDGET_H
