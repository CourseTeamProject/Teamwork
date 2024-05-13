#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CHESS_ROWS        15  //棋盘水平方向格子数
#define CHESS_COLUMES    15  //棋盘垂直方向格子数
#define RECT_WIDTH        50  //每个格子的宽
#define RECT_HEIGHT        50  //每个格式的高

#include <QMainWindow>
#include "signalchess.h"
#include <QPoint>
#include <QEvent>
#include <QPainter>
#include <QVector>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);  //绘图事件
    void mousePressEvent(QMouseEvent *); //鼠标事件
    void CheckSignal(QString str);  //检查信号类型 前缀（实际没有冒号） t：文本信息 c：棋子类型（后接一个数字 单数黑棋 双数白棋 ）r:当前回合数  p:下棋位置 x,y

private:
    void DrawChessboard();  //画棋盘
    void DrawChesses();     //画已下的棋子
    void DrawChessWithMouse(); //将要下的棋子,跟着鼠标移动

    void DrawChessAtPoint(QPainter& painter,QPoint& pt);//在pt 位置,以Painter 画棋子

    void DrawLastChess();//标识最近下的一个棋子

    int CountNearChess(SignalChess sigalChess,QPoint ptDirection);    //统计某个方向(共8个方向)上的相同颜色的棋子个数，用QPoint表示统计方向，如(1,1)表示右下方,（-1,0）表示向左

    void GameOver();    //游戏结束要做的操作
    void GameBeginnig();    //游戏开始要做的操作

    QTcpSocket *mSocket;//网络通信对象

private slots:
    void on_ConnectBtn_clicked();

    void on_sendBtn_clicked();

    void on_nowBtn_clicked();

    void on_getLoseBtn_clicked();

    void on_noReallyBtn_clicked();

    void on_getReallyBtn_clicked();

private:
    Ui::MainWindow *ui;
    QVector<SignalChess> mSignalChess;//已下的棋子座标容器
    QVector<SignalChess> mPlayedChess;

    bool mIsBlackTurn;    //当前该黑棋下 单回合下棋
    int IsRound = 0;    //回合数
    bool ChessYN = false; //是否已经赋值

    QPoint lastChess;   //记录上一个棋子
    bool lastYes = false;   //记录的上一个棋子是否有效
};
#endif // MAINWINDOW_H
