#include "mySudoku.h"
#include <iostream>
#include <ctime>
#include <random>
#include <wtypes.h>

using namespace std;

mySudoku::mySudoku() 
{
	chess = {
		{ 1,2,3,4,5,6,7,8,9 },
		{ 4,5,6,7,8,9,1,2,3 },
		{ 7,8,9,1,2,3,4,5,6 },
		{ 2,3,4,5,6,7,8,9,1 },
		{ 5,6,7,8,9,1,2,3,4 },
		{ 8,9,1,2,3,4,5,6,7 },
		{ 3,4,5,6,7,8,9,1,2 },
		{ 6,7,8,9,1,2,3,4,5 },
		{ 9,1,2,3,4,5,6,7,8 }
	};
	chessBoardInit(15);
}


mySudoku::~mySudoku()
{
}

void mySudoku::chessBoardInit(int engineCount)
{
	chessBoardChangeTwoNum(engineCount);
	changeRowNCon(engineCount);
	changeThreeRowNCol(engineCount);
}

/*�����������е�������x��y����*/
void mySudoku::_changeValue(int x, int y)
{
	for (vint & v1 : chess)
		for (int &v2 : v1)
		{
			v2 = v2 == x ? y : (v2 == y ? x : v2);
		}
}
void mySudoku::chessBoardChangeTwoNum(int engineCount)
{
	int a, b;
	std::default_random_engine e((UINT)time(0));//c++11��ͷ�ļ�random�����������
	std::uniform_int_distribution<int> u(1, 9);//c++11����������ɣ���u(e)����һ��1-9֮��������

	for (int i = 0; i < engineCount; ++i)//�任engineCount��
	{
		a = u(e), b = u(e);//����1-9֮��������
		if (a != b)
			_changeValue(a, b);
		else --i;
	}
}

/*������*/
void mySudoku::_swapRow(int x, int y)
{
	using std::swap;
	swap(chess[x], chess[y]);
}
/*������*/
void mySudoku::_swapCol(int x, int y)
{
	for (int i = 0; i < 9; ++i)
	{
		using std::swap;
		swap(chess[i][x], chess[i][y]);
	}
}
/*�����к��б�����С����Χ�ڽ����źϷ���0~2��3~5��6~8*/
void mySudoku::changeRowNCon(int engineCount)
{
	std::default_random_engine e((UINT)time(0));
	std::uniform_int_distribution<int>u(0, 2);
	int bases, x, y;

	for (int i = 0; i < engineCount; ++i)
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
void mySudoku::_swapThreeCol(int x, int y)
{
	for (int i = 0; i < 3; ++i)
		_swapCol(x + i, y + i);
}
/*x,y������0,3,6������*/
void mySudoku::_swapThreeRow(int x, int y)
{
	for (int i = 0; i < 3; ++i)
		_swapRow(x + i, y + i);
}

void mySudoku::changeThreeRowNCol(int engineCount)
{
	std::default_random_engine e((UINT)time(0));
	std::uniform_int_distribution<int>u(0, 2);
	int x, y;
	for (int i = 0; i < engineCount; ++i)
	{
		x = u(e), y = u(e);
		if (x != y)
			_swapThreeRow(3 * x, 3 * y);//0,3,6
		x = u(e), y = u(e);
		if (x != y)
			_swapThreeCol(3 * x, 3 * y);//0,3,6
	}

}

void mySudoku::printChessBoard()
{
	int i = 0;
	for (vint & v1 : chess) {
		if (i % 27 == 0)
			cout << "------------" << endl;
		for (int &v2 : v1)
		{
			cout << v2;
			if ((++i) % 3 == 0)
				cout<<"|";
		}
		cout << endl;
	}
}
