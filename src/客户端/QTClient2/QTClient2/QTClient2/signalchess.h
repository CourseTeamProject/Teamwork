#ifndef SIGNALCHESS_H
#define SIGNALCHESS_H
#include <QPoint>

class SignalChess
{


public:
    SignalChess(){}
    SignalChess(QPoint pt,bool bChessColor);  //位置和颜色为参数的构造函数
    ~SignalChess(void){}

    bool operator==(const SignalChess &t1)const // "==" SignalChess 类等于的重构函数
    {
        return ((mChessPossition == t1.mChessPossition) && (mChessColor == t1.mChessColor));
    }

    QPoint mChessPossition; //位置座标

    bool mChessColor; //颜色

};

#endif // SIGNALCHESS_H
