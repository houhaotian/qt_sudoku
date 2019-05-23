#include "mysudoku.h"
#include "hardlevel.h"

int main()
{
    MySudoku sudoku(HardLevel::master);
    sudoku.printChessBoard();

}