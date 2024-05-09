#include "Widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket;

    //收到消息时 触发阅读消息信号
    connect(mSocket,&QTcpSocket::readyRead,this,[this](){
        char str[1024]={0};
        mSocket->read(str,sizeof str);
        ui->textShow->append(str);

    });



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ConnectBtn_clicked()
{
    //连接服务器
    if(ui->IPEdit->text().isEmpty()||ui->PortEdit->text().isEmpty())
    {
        return;
    }

    //获取填写的ip和端口号
    QString ip = ui->IPEdit->text();
    int port = ui->PortEdit->text().toInt();

    mSocket->connectToHost(QHostAddress(ip),port);//连接到主机

    //当成功连接到一个主机时 会触发connected连接了信号
    connect(mSocket,&QTcpSocket::connected,this,[this](){
        QMessageBox::information(this,"提示","连接成功!");
        ui->ConnectBtn->setEnabled(false);//禁用按钮
    });


}

void Widget::on_sendBtn_clicked()
{
    //点击按钮发送消息
    mSocket->write(ui->messageEdit->text().toUtf8());


}
