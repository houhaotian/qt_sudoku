#include "mysudoku.h"
#include <iostream>
#include <ctime>
#include <random>
#include <wtypes.h>

using namespace std;

MySudoku::MySudoku(HardLevel::Levels x) : gameLevel(x)
{
    chess = {
        {8, 7, 4, 6, 3, 1, 5, 9, 2},
        {5, 9, 6, 7, 2, 8, 4, 3, 1},
        {2, 3, 1, 4, 5, 9, 6, 8, 7},
        {4, 8, 2, 1, 9, 6, 7, 5, 3},
        {7, 6, 5, 3, 8, 4, 2, 1, 9},
        {9, 1, 3, 5, 7, 2, 8, 4, 6},
        {3, 2, 9, 8, 6, 5, 1, 7, 4},
        {1, 5, 7, 2, 4, 3, 9, 6, 8},
        {6, 4, 8, 9, 1, 7, 3, 2, 5}
    };
    changeTime = 15;
    chessBoardInit(changeTime);
    truth = chess;
    HardLevel lev(gameLevel);
    for (int a = 0; a < 9; ++a)
    {
        for (int b = 0; b < 9; ++b)
        {
            if (!lev[a][b])//�����Ϊ1
                chess[a][b] = 0;//�Ͱ�ֵ��Ϊ0��������ʾ
        }
    }
}


MySudoku::~MySudoku()
{
}

void MySudoku::chessBoardInit(int engineTime)
{
    changeTwoNum(engineTime);
    changeRowNCon(engineTime);
    changeThreeRowNCol(engineTime);
}

/*�����������е�������x��y����*/
void MySudoku::_changeValue(int x, int y)
{
    for (vint & v1 : chess)
        for (int &v2 : v1)
        {
            v2 = v2 == x ? y : (v2 == y ? x : v2);
        }
}
void MySudoku::changeTwoNum(int engineTime)
{
    int a, b;
    std::default_random_engine e((UINT)time(0));//c++11��ͷ�ļ�random�����������
    std::uniform_int_distribution<int> u(1, 9);//c++11����������ɣ���u(e)����һ��1-9֮��������

    for (int i = 0; i < engineTime; ++i)//�任engineTime��
    {
        a = u(e), b = u(e);//����1-9֮��������
        if (a != b)
            _changeValue(a, b);
        else --i;
    }
}

/*������*/
void MySudoku::_swapRow(int x, int y)
{
    using std::swap;
    swap(chess[x], chess[y]);
}
/*������*/
void MySudoku::_swapCol(int x, int y)
{
    for (int i = 0; i < 9; ++i)
    {
        using std::swap;
        swap(chess[i][x], chess[i][y]);
    }
}
/*�����к��б�����С����Χ�ڽ����źϷ���0~2��3~5��6~8*/
void MySudoku::changeRowNCon(int engineTime)
{
    std::default_random_engine e((UINT)time(0));
    std::uniform_int_distribution<int>u(0, 2);
    int bases, x, y;

    for (int i = 0; i < engineTime; ++i)
    {
        bases = 3 * u(e), x = bases + u(e), y = bases + u(e);
        if (x != y)
            _swapRow(x, y);//x��y���� 0-2 3-5 6-8 ������Χ�е�һ����
        bases = 3 * u(e), x = bases + u(e), y = bases + u(e);
        if (x != y)
            _swapCol(x, y);//x��y���� 0-2 3-5 6-8 ������Χ�е�һ����
    }
}

/*x,y������0,3,6������*/
void MySudoku::_swapThreeCol(int x, int y)
{
    for (int i = 0; i < 3; ++i)
        _swapCol(x + i, y + i);
}
/*x,y������0,3,6������*/
void MySudoku::_swapThreeRow(int x, int y)
{
    for (int i = 0; i < 3; ++i)
        _swapRow(x + i, y + i);
}

void MySudoku::changeThreeRowNCol(int engineTime)
{
    std::default_random_engine e((UINT)time(0));
    std::uniform_int_distribution<int>u(0, 2);
    int x, y;
    for (int i = 0; i < engineTime; ++i)
    {
        x = u(e), y = u(e);
        if (x != y)
            _swapThreeRow(3 * x, 3 * y);//0,3,6
        x = u(e), y = u(e);
        if (x != y)
            _swapThreeCol(3 * x, 3 * y);//0,3,6
    }

}

void MySudoku::printChessBoard()
{
    int i = 0;
    for (vint & v1 : chess) {
        if (i % 27 == 0)
            cout << "------------" << endl;
        for (int &v2 : v1)
        {
            cout << v2;
            if ((++i) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}
