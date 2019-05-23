#ifndef HARDLEVEL_H
#define HARDLEVEL_H

#include <vector>


typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;


class HardLevel
{
public:
    enum Levels
    {
        easy,
        normal,
        hard,
        master
    };

    explicit HardLevel(Levels hardlevel);

    const vbool & operator[](int a)const
    {
        return defaultshow[a];
    }

private:
    void setHardLevel();
    void sayEasyWays();
    void sayNormalWays();
    void sayHardWays();
    void sayMasterWays();
    void generate_map();
    void changeRow(vbool &a, int num);

private:
    const Levels gameLevel;//难度
    std::vector<int> showNumsPerRow;//一维数组，数字为每一行中默认显示出几个数字，根据这个设置defaultshow
    vvbool defaultshow;//9x9 chessBoard的显示方式

};

#endif // HARDLEVEL_H
