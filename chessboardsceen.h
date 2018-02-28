#ifndef CHESSBOARDSCEEN_H
#define CHESSBOARDSCEEN_H

#include <QPushButton>
#include <QWidget>


#include "mySudoku/mysudoku.h"
#include "mySudoku/hardlevel.h"

namespace Ui {
class ChessBoardSceen;
}

class ChessBoardSceen : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoardSceen(QWidget *parent = 0);
    ~ChessBoardSceen();

signals:

private slots:
    void chessBoardClicked();
    void resetChessBoard(int gameLevel); //游戏重新开始，重新生成数独棋盘

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::ChessBoardSceen *ui;

    MySudoku *sudokuPower;  //生成的数独数字
    QPushButton chess[9][9];    //9X9棋盘

    int everyNumCorrectCount[9];  //存放9个数字的未被猜对的个数
    static int nowGameHardLevel;   //当前游戏难度
    static int emptyNum;   //总共有多少未猜对的格子
    static int nowSelectedNum; //高亮选中的值
    static int nowEmptyButtonX; //记录上一次选中的空白格子的X下标
    static int nowEmptyButtonY; //记录上一次选中的空白格子的Y下标
    static int onPressingBoard; //选中的格子的名字
    static int wrongTime;   //错误次数
    static int score;   //游戏得分


private:
    void initChessboard();
    void highLightSelectedButtons(int aimmedNum);

};

#endif // CHESSBOARDSCEEN_H