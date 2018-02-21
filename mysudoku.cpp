#include<random>
#include "mysudoku.h"
#include <ctime>

using namespace std;
static default_random_engine e(time(0));//c++11，头文件random,设置种子

#define change2num_count 15
#define changec_r_count 10
#define change3c_r_count 10
mysudoku::mysudoku()
{
	my_mat = {
		array_1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		array_1{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
		array_1{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
		array_1{ 2, 3, 4, 5, 6, 7, 8, 9, 1 },
		array_1{ 5, 6, 7, 8, 9, 1, 2, 3, 4 },
		array_1{ 8, 9, 1, 2, 3, 4, 5, 6, 7 },
		array_1{ 3, 4, 5, 6, 7, 8, 9, 1, 2 },
		array_1{ 6, 7, 8, 9, 1, 2, 3, 4, 5 },
		array_1{ 9, 1, 2, 3, 4, 5, 6, 7, 8 },
	};
}

mysudoku::~mysudoku()
{
}

void mysudoku::debugprint(void)
{
	for (auto & mymap : my_mat)
	{
		for (auto & x : mymap)	//基于范围的for循环（是只读的）
		{
			cout << x << " | ";
		}
		cout << endl;
	}
	cout << endl;
}

//改变数组的随机两个数字
void mysudoku::swap2num(void)
{
	uniform_int_distribution<int> u(1, 9);//c++11，随机数生成
	int i, j;

	for (int x = 0; x < change2num_count; ++x)//可以改为其它数字
	{
		i = u(e), j = u(e);//两个1-9之间的随机数
		if (i != j)
			_change_value(i, j);
		else --x;
	}
}

void mysudoku::_change_value(int lhs, int rhs)
{
	for (array_1 & mymap : my_mat)
	{
		for (int & x : mymap)
		{
			x = x == lhs ? rhs : (x == rhs ? lhs : x);
		}
	}
}

/*互换一行或一列*/
void mysudoku::swapc_r(void)
{
	std::uniform_int_distribution<int>ul(0, 2);
	int bases, i, j;
	for (int a = 0; a < changec_r_count; ++a)		//10可以改为其它数字
	{
		bases = 3 * ul(e), i = bases + ul(e), j = bases + ul(e);
		if (i != j)
			_swap_row(i, j);//i与j均在 0-2 3-5 6-8 三个范围中的一个里
		bases = 3 * ul(e), i = bases + ul(e), j = bases + ul(e);
		if (i != j)
			_swap_col(i, j);
	}
}


void mysudoku::_swap_row(int lhs, int rhs)
{
	using std::swap;
	swap(my_mat[lhs], my_mat[rhs]);
}

void mysudoku::_swap_col(int lhs, int rhs)
{
	using std::swap;
	for (int i = 0; i < 9; ++i)
	{
		swap(my_mat[i][lhs], my_mat[i][rhs]);
	}
}



/*互换三行或三列*/
void mysudoku::swap3c_r(void)
{
	std::uniform_int_distribution<int>ul(0, 2);
	int i, j;

	for (int a = 0; a < change3c_r_count; ++a)	//10可以改为其它数字
	{
		i = ul(e), j = ul(e);
		if (i != j)
			_swap_3cols(3 * i, 3 * j);//0 3 6
		i = ul(e), j = ul(e);
		if (i != j)
			_swap_3raws(3 * i, 3 * j);// 0 3 6
	}
}


void mysudoku::_swap_3cols(int lhs, int rhs)//0,3,6
{
	for (int i = 0; i < 3; ++i)
		_swap_col(lhs + i, rhs + i);
}


void mysudoku::_swap_3raws(int lhs, int rhs)//0,3,6
{
	for (int i = 0; i < 3; ++i)
		_swap_row(lhs + i, rhs + i);
}


//初始化
void mysudoku::init_mymat(void)
{
	swap2num();
	swapc_r();
	swap3c_r();
}