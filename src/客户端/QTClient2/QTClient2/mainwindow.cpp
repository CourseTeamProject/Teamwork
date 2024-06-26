#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpSocket>
#include <QRadialGradient>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //设置窗口大小,并固定
    resize((CHESS_COLUMES + 2)*RECT_WIDTH + 500 +150 ,(CHESS_ROWS + 2)*RECT_HEIGHT+50);//基础宽 高 17*50+500 850+500 1350  高:17*50
    setMaximumSize((CHESS_COLUMES + 2)*RECT_WIDTH  + 500 + 150,(CHESS_ROWS + 2)*RECT_HEIGHT+50);
    setMinimumSize((CHESS_COLUMES + 2)*RECT_WIDTH + 500 + 150 ,(CHESS_ROWS + 2)*RECT_HEIGHT+50);
    //黑子先下
    mIsBlackTurn = true;

    //准备按钮初始化
    ui->getReallyBtn->setEnabled(true);//准备按钮可按
    ui->noReallyBtn->setDisabled(true);//取消不可以按

    //认输按钮初始化
    ui->getLoseBtn->setDisabled(true);//认输不可按


    mSocket = new QTcpSocket;

    //收到消息时 触发阅读消息信号
    connect(mSocket,&QTcpSocket::readyRead,this,[this](){
        char str[1024]={0};
        mSocket->read(str,sizeof str);
        CheckSignal(str);

    });




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    DrawChessboard();        //画棋盘
    DrawChesses();            //画棋子
    DrawChessWithMouse();    //画鼠标带着一个棋子（当前放的棋子形状）
    DrawLastChess();        //画上一个下的棋子
    update();
}

void MainWindow::DrawChessboard()//画棋盘
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true); //渲染类型为高质量抗锯齿
    painter.setBrush(QColor(252,252,188));//设置填冲颜色 棋盘的底色
    painter.setPen(QPen(QColor(Qt::black),2));//设置画笔颜色,线粗,默认为实线

    for(int i = 0;i<CHESS_COLUMES; i++)//遍历每一个座标点,画出每一个矩形.
    {
        for (int j = 0; j<CHESS_ROWS; j++)
        {

            painter.drawRect( (i+1)*RECT_WIDTH,(j+1)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);//绘制一个左上角坐标为(x,y)，宽为50，高为50的矩形
        }
    }
}

void MainWindow::DrawChesses()//画已下的棋子
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent))); //设置画笔颜色 透明黑色,same as QColor(0, 0, 0, 0)

    for (int i = 0; i<mPlayedChess.size(); i++) //遍历每一个已下的棋子
    {
        SignalChess signalchess = mPlayedChess[i];

        //每个已下棋子中心点座标和渐变填冲焦点座标
        QPoint ptcentor((signalchess.mChessPossition.x()+1)*RECT_WIDTH,(signalchess.mChessPossition.y()+1)*RECT_HEIGHT);
        QPoint ptfocal((signalchess.mChessPossition.x()+1)*RECT_WIDTH,(signalchess.mChessPossition.y()+1)*RECT_HEIGHT);
        //定义渐变填冲
        QRadialGradient radialGradient(ptcentor,RECT_WIDTH/3,ptfocal);

        if (signalchess.mChessColor)
        {
            //painter.setBrush(Qt::black);

            //如果是黑子,定义黑色渐变
            radialGradient.setColorAt(0,QColor(0,0,0,255));
            radialGradient.setColorAt(1,QColor(100,100,100,255));
        }
        else
        {
            //painter.setBrush(Qt::white);
            //如果是白子,定义白色渐变
            radialGradient.setColorAt(0,QColor(255,255,255,255));
            radialGradient.setColorAt(1,QColor(180,180,180,255));
        }


        painter.setBrush(radialGradient);//定义渐变填冲

        DrawChessAtPoint(painter,ptcentor); //以ptcentor 为中心画出棋子
    }
}

void MainWindow::DrawChessAtPoint(QPainter& painter,QPoint& pt)  //以pt 为中心画出1/3 棋盘方块宽度为半径的圆
{
    //painter.drawRect( (pt.x()+0.5)*RECT_WIDTH,(pt.y()+0.5)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);

    //QPoint ptCenter((pt.x()+0.5)*RECT_WIDTH,(pt.y()+0.5)*RECT_HEIGHT);
    painter.drawEllipse(pt,RECT_WIDTH / 3,RECT_HEIGHT / 3);
}


void MainWindow::DrawChessWithMouse() //将要下的棋子,跟着鼠标移动
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    if (mIsBlackTurn)
    {
        painter.setBrush(Qt::black);//设置填冲颜色
    }
    else
    {
        painter.setBrush(Qt::white);
    }

    //mapFromGlobal, 转换座标为相对座标
    QPoint cPoint(mapFromGlobal(QCursor::pos()));
    //只有在棋盘区域,才绘制圆跟随鼠标
    //qDebug()<<"cPoint.x()="<<cPoint.x()/RECT_WIDTH<<"cPoint.y()"<<cPoint.y()/RECT_WIDTH;

    if (! (cPoint.x()/RECT_WIDTH<1 || cPoint.x()/RECT_WIDTH>CHESS_COLUMES || cPoint.y()/RECT_HEIGHT<1 || cPoint.y()/RECT_HEIGHT>CHESS_ROWS))

       painter.drawEllipse(cPoint,RECT_WIDTH / 3,RECT_HEIGHT / 3);//以cPoint 为中心画出1/3 棋盘方块宽度为半径的圆

}

void MainWindow::DrawLastChess()//标记上一个棋子
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(255,110,110),3));//设置画笔颜色,线粗,默认为实线
    QPoint newChess;
    newChess.setX((lastChess.x()+1)*RECT_WIDTH);
    newChess.setY((lastChess.y()+1)*RECT_HEIGHT);
    if(lastYes) //更新的棋子有效
    {
        qDebug() << "yes";
        painter.drawLine(newChess.x(),newChess.y()-4, newChess.x(),newChess.y()-6);     //上
        painter.drawLine(newChess.x()-4,newChess.y(), newChess.x()-6,newChess.y());     //左
        painter.drawLine(newChess.x(),newChess.y()+4, newChess.x(),newChess.y()+6);     //下
        painter.drawLine(newChess.x()+4,newChess.y(), newChess.x()+6,newChess.y());     //右
    }



}







void MainWindow::mousePressEvent(QMouseEvent * e) //鼠标按下事件
{
    //求鼠标点击处的棋子点pt
    QPoint pt;
    int x=e->pos().x() ;
    int y=e->pos().y();

    //测试点击坐标
    qDebug() << e->pos();


    //如果鼠标不是在棋盘区域按下,则放弃此鼠标按压事件
    if ((x/RECT_WIDTH<1 || x/RECT_WIDTH>CHESS_COLUMES || y/RECT_HEIGHT<1 || y/RECT_HEIGHT>CHESS_ROWS))
        return;

    //游戏还没开始 不能下棋
    if(IsRound==0)
    {
        return ;
    }

    //如果当前不是自己回合,放弃此鼠标按压事件
    if(mIsBlackTurn)    //黑子为单数回合
    {
        if(IsRound%2!=1)
        {
            return ;
        }
    }
    else    //白子为双数回合
    {
        if(IsRound%2!=0)
        {
            return ;
        }
    }

    //判定鼠标的位置更接近哪一个座标点, 将该座标点作为要下棋子的点
    if (x%RECT_WIDTH<=RECT_WIDTH/2)

         pt.setX( x / RECT_WIDTH-1);
    else
        pt.setX( x / RECT_WIDTH);

    if (y%RECT_HEIGHT<=RECT_HEIGHT/2)

         pt.setY( y / RECT_HEIGHT-1);
    else
        pt.setY( y / RECT_HEIGHT);

    //qDebug()<<"x="<<x<<","<<"x%Rect_Width="<<x%RECT_WIDTH<<",pt.x="<<pt.x();
    //qDebug()<<"y="<<y<<","<<"y%Rect_height="<<x%RECT_HEIGHT<<",pt.y="<<pt.y();


    //如果已存在棋子，就什么也不做
    for (int i = 0; i<mPlayedChess.size(); i++) //遍历已下棋子的座标
    {
        SignalChess signalchess = mPlayedChess[i];
        if (signalchess.mChessPossition == pt) //判定是否已存在棋子,若是,则放弃本次鼠标事件
        {
            return;
        }
    }
    //不存在棋子，则构造一个棋子,并添加到已下棋子容器中
    SignalChess signalchess(pt,mIsBlackTurn);
    mPlayedChess.append(signalchess);//添加

    //标记更新的棋子
    lastYes = true;
    lastChess.setX(x);
    lastChess.setY(y);


    //下棋了 要发送下棋信息
    mSocket->write(("p"+QString::number(pt.x())+","+QString::number(pt.y())).toUtf8());

    //统计4个方向是否五子连
    int nLeft =            CountNearChess(signalchess,QPoint(-1,0));
    int nLeftUp =        CountNearChess(signalchess,QPoint(-1,-1));
    int nUp =            CountNearChess(signalchess,QPoint(0,-1));
    int nRightUp =        CountNearChess(signalchess,QPoint(1,-1));
    int nRight =        CountNearChess(signalchess,QPoint(1,0));
    int nRightDown =    CountNearChess(signalchess,QPoint(1,1));
    int nDown =            CountNearChess(signalchess,QPoint(0,1));
    int nLeftDown =        CountNearChess(signalchess,QPoint(-1,1));



    if ( (nLeft + nRight) >= 4 ||
         (nLeftUp + nRightDown) >= 4 ||
         (nUp + nDown) >= 4 ||
         (nRightUp + nLeftDown) >= 4 )
    {
        //自己胜利
        QString str = mIsBlackTurn?"黑棋获胜！":"白棋获胜！";
        QMessageBox::information(NULL,  "GAME OVER",str, QMessageBox::Yes , QMessageBox::Yes);

        (mIsBlackTurn)?ui->textShow->append("游戏结束,黑棋获胜。"):ui->textShow->append("游戏结束,白棋获胜。");
        mPlayedChess.clear();
        IsRound = 0;
        GameOver();
        //NewGame();
        return;
    }

    ui->textShow->append("现在是第"+QString::number(IsRound+1)+"回合，现在轮到对方下棋！");

    //换另一方下棋了
    //mIsBlackTurn = !mIsBlackTurn;
}


int MainWindow::CountNearChess(SignalChess signalchess,QPoint ptDirection)//统计相近有多少棋子
{
    int nCount = 0; //记录相连棋子个数
    SignalChess item=signalchess;
    item.mChessPossition += ptDirection;//产生待判定的座标

    while (mPlayedChess.contains(item)) //循环确认待判定的座标,item 和signalchess 只是座标位置不同,颜色相同
    {
        nCount++;
        item.mChessPossition += ptDirection; //产生下一个待判定的座标.
    }
    return nCount; //返回相连棋子个数
}

void MainWindow::GameOver()    //游戏结束要做的按钮设置操作
{
    //标记更新的棋子无效
    lastYes = false;

    ui->getLoseBtn->setDisabled(true);//认输按钮不可以按
    ui->getReallyBtn->setEnabled(true);//准备按钮可按
    ui->noReallyBtn->setDisabled(true);//取消不可以按
}
void MainWindow::GameBeginnig()    //游戏开始要做的按钮设置操作
{
    ui->getLoseBtn->setEnabled(true);//认输按钮可以按
    ui->getReallyBtn->setDisabled(true);//准备按钮不可按
    ui->noReallyBtn->setDisabled(true);//取消不可以按
}



void MainWindow::on_ConnectBtn_clicked()//连接服务器
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

void MainWindow::CheckSignal(QString str)
{
    QString Connect = str;
    Connect.remove(0,1);//实际内容移除前缀
    if(str[0]=="t")//文本信息
    {
        ui->textShow->append(Connect);
    }
    else if(str[0]=="c")//棋子
    {
        if(!ChessYN)    //还没有给棋子颜色
        {
            if(Connect.toInt()%2==0)    //给白色
            {
                mIsBlackTurn = false;
            }
            else    //给黑色
            {
                mIsBlackTurn = true;
            }
            ChessYN = true;
        }

    }
    else if(str[0]=="r")       //当前回合数
    {
        IsRound = Connect.toInt();
        if(IsRound==1)
        {
            GameBeginnig();
            ui->textShow->append("游戏开始！");
            if(mIsBlackTurn)
            {
                ui->textShow->append("您是黑棋，现在轮到您下棋");
            }
            else
            {
                ui->textShow->append("您是白棋");
            }

        }
    }
    else if(str[0]=="G")
    {
        if(Connect=="over")
        {
            //避免重复结算
            if(IsRound==0)
            {
                return;
            }

            //自己胜利
            QString str = mIsBlackTurn?"黑棋获胜！":"白棋获胜！";
            QMessageBox::information(NULL,  "GAME OVER",str, QMessageBox::Yes , QMessageBox::Yes);

            (mIsBlackTurn)?ui->textShow->append("游戏结束,黑棋获胜。"):ui->textShow->append("游戏结束,白棋获胜。");
            mPlayedChess.clear();
            IsRound = 0;
            GameOver();

            //NewGame();
            mSocket->write("Oover");
            return;
        }
    }
    else if(str[0]=="p")
    {
        IsRound++;
        //分割坐标
        QStringList subsList = Connect.split(QChar(','));
        int x = subsList[0].toInt();
        int y = subsList[1].toInt();

        //设置坐标
        QPoint pt;
        pt.setX(x);
        pt.setY(y);

        //标记更新的棋子
        lastYes = true;
        lastChess.setX(x);
        lastChess.setY(y);

        for (int i = 0; i<mPlayedChess.size(); i++) //遍历已下棋子的座标
        {
            SignalChess signalchess = mPlayedChess[i];
            if (signalchess.mChessPossition == pt) //判定是否已存在棋子,若是,则放弃本次鼠标事件
            {
                return;
            }
        }

        //添加对方的棋子
        SignalChess signalchess(pt,!mIsBlackTurn);
        mPlayedChess.append(signalchess);//添加

        //统计4个方向是否五子连
        int nLeft =            CountNearChess(signalchess,QPoint(-1,0));
        int nLeftUp =        CountNearChess(signalchess,QPoint(-1,-1));
        int nUp =            CountNearChess(signalchess,QPoint(0,-1));
        int nRightUp =        CountNearChess(signalchess,QPoint(1,-1));
        int nRight =        CountNearChess(signalchess,QPoint(1,0));
        int nRightDown =    CountNearChess(signalchess,QPoint(1,1));
        int nDown =            CountNearChess(signalchess,QPoint(0,1));
        int nLeftDown =        CountNearChess(signalchess,QPoint(-1,1));



        if ( (nLeft + nRight) >= 4 ||
             (nLeftUp + nRightDown) >= 4 ||
             (nUp + nDown) >= 4 ||
             (nRightUp + nLeftDown) >= 4 )
        {

            QString str = (!mIsBlackTurn)?"黑棋获胜！":"白棋获胜！";
            QMessageBox::information(NULL,  "GAME OVER",str, QMessageBox::Yes , QMessageBox::Yes);
            (!mIsBlackTurn)?ui->textShow->append("游戏结束,黑棋获胜。"):ui->textShow->append("游戏结束,白棋获胜。");
            mPlayedChess.clear();
            IsRound = 0;
            //NewGame();
            mSocket->write("Oover");

            GameOver();

            return;
        }
        ui->textShow->append("现在是第"+QString::number(IsRound)+"回合，现在轮到您下棋！");

    }
}




void MainWindow::on_sendBtn_clicked()
{
    //点击按钮发送消息
    mSocket->write(("t"+ui->messageEdit->text()).toUtf8());

}
void MainWindow::on_nowBtn_clicked()
{
    ui->textShow->append("你的棋子:");
    if(mIsBlackTurn)
    {
        ui->textShow->append("黑子");
    }
    else
    {
        ui->textShow->append("白子");
    }
    ui->textShow->append("当前回合:");
    ui->textShow->append(QString::number(IsRound));
}

void MainWindow::on_getLoseBtn_clicked()        //认输
{
    QMessageBox asklose(QMessageBox::Question,QString(tr("认输")),QString(tr("你确定要认输吗？")),QMessageBox::Yes|QMessageBox::No);
    asklose.setButtonText(QMessageBox::Yes,QString(tr("是")));  //方式1
    asklose.button(QMessageBox::No)->setText(tr("否"));    //方式2
    int Result = asklose.exec();
    if(Result == QMessageBox::Yes)
    {

        QString str = (!mIsBlackTurn)?"黑棋获胜！":"白棋获胜！";
        QMessageBox::information(NULL,  "GAME OVER",str, QMessageBox::Yes , QMessageBox::Yes);
        (!mIsBlackTurn)?ui->textShow->append("游戏结束,黑棋获胜。"):ui->textShow->append("游戏结束,白棋获胜。");
        mPlayedChess.clear();
        IsRound = 0;

        GameOver();
        //发送认输信号
        mSocket->write("Gover");
    }

}

void MainWindow::on_noReallyBtn_clicked()//取消准备
{
    ui->getReallyBtn->setEnabled(true);//准备按钮可按
    ui->noReallyBtn->setDisabled(true);//取消不可以按
    mSocket->write("R-");   //Really-
}

void MainWindow::on_getReallyBtn_clicked()//准备
{
    ui->getReallyBtn->setDisabled(true);//准备按钮不可按
    ui->noReallyBtn->setEnabled(true);//取消准备可以按
    mSocket->write("R+");   //Really+
}
