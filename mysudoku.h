#pragma once
#include<iostream>
#include<array>

using namespace std;

typedef array<int, 9> array_1;
typedef array<array_1, 9> array_2;

class mysudoku
{
public:
	mysudoku();
	~mysudoku();

	//改变数组的随机两个数字
	void swap2num(void);
	/*互换三行或三列*/
	void swap3c_r(void);
	/*互换一行或一列*/
	void swapc_r(void);
	
	void init_mymat(void);
	void debugprint(void);

private:
	array_2 my_mat;

private:
	void _change_value(int lhs, int rhs);

	void _swap_row(int lhs, int rhs);
	void _swap_col(int lhs, int rhs);

	void _swap_3cols(int lhs, int rhs);
	void _swap_3raws(int lhs, int rhs);
};

