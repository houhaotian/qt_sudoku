#pragma once
#include <vector>
#include "hardlevel.h"

typedef std::vector<int>  vint;
typedef std::vector<vint> vvint;

class MySudoku
{
public:
    explicit MySudoku(HardLevel::Levels x);
    ~MySudoku();


    void chessBoardInit(int engineTime);
    void printChessBoard();
    const vint & operator[](int x)const {
        return chess[x];
    }//运算符重载
    vvint truth;
private:
    vvint chess;

    int changeTime;//初始化时做变换的次数
    HardLevel::Levels gameLevel;//难度
private:
    void _changeValue(int column, int row);
    void changeTwoNum(int engineTime);

    void _swapRow(int x, int y);
    void _swapCol(int x, int y);
    void changeRowNCon(int engineTime);

    void _swapThreeCol(int x, int y);
    void _swapThreeRow(int x, int y);
    void changeThreeRowNCol(int engineTime);
};
