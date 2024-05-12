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

    void on_sendBtn_clicked();

    void CheckSignal(QString str);      //检查收到的信息类型

    void on_peopleBtn_clicked();

    void on_GameBtn_clicked();

    void on_RoundBtn_clicked();

private:
    Ui::Widget *ui;

    int m_iClientCount;
    QList<QTcpSocket*> listClient;
    QTcpServer *mServer;
    QTcpSocket *mSocket;//通信套接字
    int mPort;//端口号

    int IsRound = 0;    //第0回合控制双方不能下棋
    int people = 0;     //连接人数
    int Really = 0;     //准备人数
};
#endif // WIDGET_H
