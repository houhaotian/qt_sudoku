#pragma once
#include <vector>

typedef std::vector<int>  vint;
typedef std::vector<vint> vvint;

class mySudoku
{
public:
	mySudoku();
	~mySudoku();

	
	void chessBoardInit(int engineCount);
	void printChessBoard();
    const vint & operator[](int x)const { return chess[x]; }//运算符重载

private:
	vvint chess;
private:
	void _changeValue(int column, int row);
	void chessBoardChangeTwoNum(int engineCount);

	void _swapRow(int x, int y);
	void _swapCol(int x, int y);
	void changeRowNCon(int engineCount);

	void _swapThreeCol(int x, int y);
	void _swapThreeRow(int x, int y);
	void changeThreeRowNCol(int engineCount);
};
