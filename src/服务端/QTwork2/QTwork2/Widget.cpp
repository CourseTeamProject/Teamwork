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
    //TCP-监听
    mServer = new QTcpServer(this);
    //tcpSocket = new QTcpSocket(this);
    mServer->listen(QHostAddress::Any, 9999);

    //newConnection代表有新的连接
    connect(mServer, &QTcpServer::newConnection,
        [=]()
    {
        people++;

        //取出建立好连接的套接字
        mSocket = mServer->nextPendingConnection();

        listClient.append(mSocket);//将生成的socket添加到容器里
        m_iClientCount++;

        //获取对方的IP和端口
        QString ip = mSocket->peerAddress().toString();
        quint16 port = mSocket->peerPort();
        QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
        qDebug() << temp << endl;
        ui->messageText->append(temp);//不用settext 这样会覆盖之前的消息

        mSocket->write(("c"+QString::number(people)).toUtf8()); //发给客户端几个人连着



        //接收信息  必须放到连接中的槽函数 不然tcpsocket就是一个野指针
        //connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::ReadData);

        connect(mSocket, &QTcpSocket::readyRead,
            [=]()
        {

            QByteArray buffer;
            //利用for循环循环列表中的每一个连接进来的客户端，判断是哪一个客户端发的数据
            for (int i = 0; i < listClient.count(); i++)
            {
                mSocket = listClient.at(i);
                buffer = mSocket->readAll();
                if (buffer.length() != 0)   //如果检测到接收到的数据长度不为0，则代表是这个客户端发送的数据
                    ui->messageText->append("客户端：" + buffer);//不用settext 这样会覆盖之前的消息

                CheckSignal(buffer);
            }
        });
    });

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
    /*
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
    }*/

}

void Widget::on_sendBtn_clicked()
{
    //点击按钮发送消息
    for (int i = 0; i < listClient.count(); i++)
    {
        mSocket = listClient.at(i);
        mSocket->write(("t"+ui->messageEdit->text()).toUtf8());
    }

}


void Widget::CheckSignal(QString str)
{
    QString Connect = str;
    Connect.remove(0,1);//实际内容移除前缀


    if(str[0]=="t")//文本信息
    {
        ui->messageText->append(Connect);

        //发给对手
        for (int i = 0; i < listClient.count(); i++)
        {
            mSocket = listClient.at(i);
            mSocket->write(str.toUtf8());
        }
    }
    else if(str[0]=="G") //认输
    {
        IsRound = 0;
        for (int i = 0; i < listClient.count(); i++)
        {
            mSocket = listClient.at(i);
            mSocket->write(str.toUtf8());
            Really = 0;
            //发个大家 下棋回合
            //mSocket->write(("r"+QString::number(IsRound)).toUtf8());
        }
    }
    else if(str[0]=="p")
    {
        IsRound++;
        //发给对手 下棋位置
        for (int i = 0; i < listClient.count(); i++)
        {
            mSocket = listClient.at(i);
            mSocket->write(str.toUtf8());

            //发个大家 下棋回合
            //mSocket->write(("r"+QString::number(IsRound)).toUtf8());
        }

    }
    else if(str[0]=="R")
    {
        if(Connect=="+")
        {
            Really++;
            if(Really==2)
            {
                IsRound = 1;
                for (int i = 0; i < listClient.count(); i++)
                {
                    mSocket = listClient.at(i);
                    mSocket->write(("r"+QString::number(IsRound)).toUtf8());
                }
            }
        }
        if(Connect=="-")
        {
            Really--;
        }
    }
    else if(str[0]=="O")//Oover 游戏结束
    {
        if(Connect=="over")
        {
            IsRound = 0;
            Really = 0;
        }

    }

}



void Widget::on_peopleBtn_clicked()//发给客户端几个人连着
{
    for (int i = 0; i < listClient.count(); i++)
    {
        mSocket = listClient.at(i);
        mSocket->write(("c"+QString::number(people)).toUtf8()); //发给客户端几个人连着
    }

    ui->messageText->append(("c"+QString::number(people)).toUtf8());
}

void Widget::on_GameBtn_clicked()//开始游戏 回合置为1
{
    IsRound = 1;
    for (int i = 0; i < listClient.count(); i++)
    {
        mSocket = listClient.at(i);
        mSocket->write(("r"+QString::number(IsRound)).toUtf8());
    }
}

void Widget::on_RoundBtn_clicked()
{
    ui->messageText->append(("当前人数:"+QString::number(people)).toUtf8());
    ui->messageText->append(("当前回合:"+QString::number(IsRound)).toUtf8());
}
