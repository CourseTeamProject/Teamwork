#include "Widget.h"
#include "ui_Widget.h"
#include <QTcpServer>
#include <QHostInfo>    //主机信息
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mServer = new QTcpServer(this);
    mSocket = new QTcpSocket(this);

}

Widget::~Widget()
{

    delete ui;
}


void Widget::on_HostInfoBtn_clicked()
{

    //获取本主机信息
    QString hostName = QHostInfo::localHostName();//获取本机名

    QHostInfo info;//主机信息对象
    info = QHostInfo::fromName(hostName);//获取主机名 返回主机信息对象
    QList<QHostAddress> addressLi = info.addresses();//获取本机网络ip地址

    ui->textEdit->append(hostName);

    foreach (QHostAddress address,addressLi) {
        ui->textEdit->append("***********");
        ui->textEdit->append(address.toString());
    }


}

void Widget::on_ListenBtn_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        return;
    }

    mPort = ui->lineEdit->text().toInt();//获取填写的端口号

    bool flag = mServer->listen(QHostAddress::Any,mPort);//服务器监听
    if(flag)
    {




        //监听成功
        QMessageBox::information(this,"提示","监听成功！");

        //当有客户端成功连接到服务器时，会触发信号
        connect(mServer,&QTcpServer::newConnection,this,[this](){


            //准备接收并处理消息 进行通信
            //nextPendingConnection返回下一个即将连接到套接字
            mSocket = mServer->nextPendingConnection();

            //当有新信息时 会触发
            connect(mSocket,&QTcpSocket::readyRead,this,[this](){
                char str[1024] = {0};
                mSocket->read(str,sizeof str);
                ui->messageText->append(str);
            });

        });



    }
    else
    {
        //监听失败
        QMessageBox::warning(this,"提示","监听失败！");
    }

}

void Widget::on_sendBtn_clicked()
{
    mSocket->write(ui->messageEdit->text().toUtf8());
}
