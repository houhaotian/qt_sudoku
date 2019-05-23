#include "hardlevel.h"
#include <random>
#include <ctime>

::std::default_random_engine e(time(0)); //c++11，头文件random，随机数种子


HardLevel::HardLevel(Levels hardlevel)
    : gameLevel(hardlevel)
    , showNumsPerRow(9, 0)
    , defaultshow(9, vbool(9, 0))
{
    setHardLevel();
    generate_map();

}

void HardLevel::setHardLevel()
{
    if (easy == gameLevel) {
        sayEasyWays();
    }
    else if (normal == gameLevel) {
        sayNormalWays();
    }
    else if (hard == gameLevel) {
        sayHardWays();
    }
    else if (master == gameLevel) {
        sayMasterWays();
    }
}


void HardLevel::sayEasyWays()
{
    //36-39个
    std::uniform_int_distribution<int> us(4, 6);
    showNumsPerRow[0] = showNumsPerRow[3] = showNumsPerRow[6] = us(e);
    std::uniform_int_distribution<int> um(3, 4);
    showNumsPerRow[1] = showNumsPerRow[7] = um(e);
    showNumsPerRow[2] = showNumsPerRow[5] = showNumsPerRow[8] = int((33 - (3 * showNumsPerRow[0] + 2 * showNumsPerRow[1])) / 3);
    std::uniform_int_distribution<int> un(4, 6);
    showNumsPerRow[4] = un(e);
}

void HardLevel::sayNormalWays()
{
    //30-36
    std::uniform_int_distribution<int> us(3, 6);
    showNumsPerRow[0] = showNumsPerRow[3] = showNumsPerRow[6] = us(e);
    std::uniform_int_distribution<int> um(2, 3);
    showNumsPerRow[1] = showNumsPerRow[7] = um(e);
    showNumsPerRow[2] = showNumsPerRow[5] = showNumsPerRow[8] = int((28 - (3 * showNumsPerRow[0] + 2 * showNumsPerRow[1])) / 3);
    std::uniform_int_distribution<int> un(3, 5);
    showNumsPerRow[4] = un(e);
}

void HardLevel::sayHardWays()
{
    //29-31
    std::uniform_int_distribution<int> us(3, 5);
    showNumsPerRow[0] = showNumsPerRow[8] = us(e);
    showNumsPerRow[1] = showNumsPerRow[7] = 7 - showNumsPerRow[0];
    std::uniform_int_distribution<int> ud(2, 3);
    showNumsPerRow[2] = showNumsPerRow[6] = ud(e);
    showNumsPerRow[3] = showNumsPerRow[5] = 7 - showNumsPerRow[2];
    std::uniform_int_distribution<int> ul(1, 3);
    showNumsPerRow[4] = ul(e);
}

void HardLevel::sayMasterWays()
{
    //27-29
    std::uniform_int_distribution<int> us(3, 5);
    showNumsPerRow[0] = showNumsPerRow[8] = us(e);
    showNumsPerRow[1] = showNumsPerRow[7] = 6 - showNumsPerRow[0];
    std::uniform_int_distribution<int> ud(2, 3);
    showNumsPerRow[2] = showNumsPerRow[6] = ud(e);
    showNumsPerRow[3] = showNumsPerRow[5] = 7 - showNumsPerRow[2];
    std::uniform_int_distribution<int> ul(1, 3);
    showNumsPerRow[4] = ul(e);
}

void HardLevel::generate_map()
{
    if (gameLevel < normal)
        for (int a = 0; a < 9; ++a)
        {
            changeRow(defaultshow[a], showNumsPerRow[a]);
        }
    else
    {
        for (int a = 0; a < 5; ++a)
        {
            changeRow(defaultshow[a], showNumsPerRow[a]);
        }
        for (int a = 5; a < 9; ++a)
        {
            defaultshow[a] = defaultshow[8 - a];//困难的地狱的对称
        }
    }
}

void HardLevel::changeRow(vbool &a, int num)
{
    int s = 0;//设置为1的数字的个数
    std::uniform_int_distribution<int> un(1, 9 - s);//范围
    int n = un(e);//e仍然是难度函数的前面声明为static的引擎，在上面的范围里产生一个随机数，第n个数字设置为1，即显示
    int temp = 0;
    vbool::iterator i = a.begin();
    do {
        if (0 == *i)
            temp++;
        if (temp == n)
        {
            *i = 1;
            if (++s == num)break;
            i = a.begin();//继续从头开始循环
            std::uniform_int_distribution<int>ud(1, 9 - s);
            n = ud(e); temp = 0;
        }
        else ++i;
    } while (i != a.end());
}
