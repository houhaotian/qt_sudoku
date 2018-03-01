#include "chessboardsceen.h"
#include "ui_chessboardsceen.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>

int ChessBoardSceen::nowSelectedNum = 0;
int ChessBoardSceen::nowGameHardLevel = 0;
int ChessBoardSceen::onPressingBoard = -1;
int ChessBoardSceen::nowEmptyButtonX = -1;
int ChessBoardSceen::nowEmptyButtonY = -1;
int ChessBoardSceen::emptyNum = 0;
int ChessBoardSceen::wrongTime = 0;
int ChessBoardSceen::score = 0;


ChessBoardSceen::ChessBoardSceen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessBoardSceen)
{
    ui->setupUi(this);

    //开启布局，填入棋盘
    initChessboard();
    timerId = startTimer(1000);
    timerCount = 0;

    connect(this, SIGNAL(beginningNewGame(int)),this, SLOT(resetChessBoard(int)));
}

ChessBoardSceen::~ChessBoardSceen()
{
    delete ui;
}

void ChessBoardSceen::chessBoardClicked()
{
    QPushButton * btn = qobject_cast<QPushButton *>(sender());
    int n = btn->accessibleName().toInt();
    int x_Pos = n / 10, y_Pos = n % 10;//获得过来的格子的下标
    int aimmedNum = chess[x_Pos][y_Pos].text().toInt(); //点选的格子的数字

    if (aimmedNum == 0)//选中的是空白格子
    {
        if (nowEmptyButtonX == -1)//上一次还未选过
        {
            onPressingBoard = n;    //记录当前选中的格子的名字
            chess[x_Pos][y_Pos].setStyleSheet(QLatin1String("background-color: #ffaa7f;\n"
                                                        "font: 14pt \"Microsoft YaHei UI\";\n"
                                                        "color: #ffffff;"));

            nowEmptyButtonX = x_Pos;//记录上一次选的格子
            nowEmptyButtonY = y_Pos;
        }
        else    //上一次有在选的空白格子
        {
            if(nowEmptyButtonX == x_Pos &&  nowEmptyButtonY == y_Pos)   //重复选一个格子
            {
                onPressingBoard = -1;
                chess[nowEmptyButtonX][nowEmptyButtonY].setStyleSheet(
                            QLatin1String("background-color: #3366CC;\n"
                                          "font: 14pt \"Microsoft YaHei UI\";\n"
                                          "color: #ffffff;"));
                nowEmptyButtonX = -1;
                nowEmptyButtonY = -1;

            }
            else //选不一样的格子
            {
                onPressingBoard = n;
                chess[nowEmptyButtonX][nowEmptyButtonY].setStyleSheet(
                            QLatin1String("background-color: #3366CC;\n"
                                          "font: 14pt \"Microsoft YaHei UI\";\n"
                                          "color: #ffffff;"));

                chess[x_Pos][y_Pos].setStyleSheet(
                            QLatin1String("background-color: #ffaa7f;\n"
                                          "font: 14pt \"Microsoft YaHei UI\";\n"
                                          "color: #ffffff;"));
                nowEmptyButtonX = x_Pos;
                nowEmptyButtonY = y_Pos;
            }

        }
    }
    else/*高亮选中的值*/
    {
        highLightSelectedButtons(aimmedNum);
    }
}

void ChessBoardSceen::resetChessBoard(int gameLevel)
{
    delete sudokuPower;
    QString temp;
    sudokuPower = new MySudoku(gameLevel);
    MySudoku & shortNameSudoku = *sudokuPower;

    wrongTime = 0;
    nowGameHardLevel = gameLevel;
    nowSelectedNum = 0;//游戏重新开始
    onPressingBoard = -1;
    nowEmptyButtonX = -1;
    nowEmptyButtonY = -1;
    emptyNum = 0;
    score = 0;
    timerCount = 0;

    for(int i = 0; i < 9; ++i)
    {
        everyNumCorrectCount[i] = 0;
    }
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            chess[i][j].setText(temp.setNum(shortNameSudoku[i][j]));
            chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                    "font: 14pt \"Microsoft YaHei UI\";\n"
                                                    "color: #ffffff;"));
            if (0 == shortNameSudoku[i][j])
            {
                chess[i][j].setText("");
                everyNumCorrectCount[shortNameSudoku.truth[i][j]-1]++;
                emptyNum++;
            }
        }
    }
}

void ChessBoardSceen::highLightSelectedButtons(int aimmedNum)
{
    /*高亮选中数字*/
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (aimmedNum == chess[i][j].text().toInt()) {
                chess[i][j].setStyleSheet(QLatin1String("background-color: #55aa7f;\n"
                    "font: 14pt \"Microsoft YaHei UI\";\n"
                    "color: #000000;"));
            }
        }
    }
    /*如果是刚开始游戏，则记录选中的值*/
    if (nowSelectedNum == 0)
    {
        nowSelectedNum = aimmedNum;
    }
    /*否则还原上一次选中的值*/
    else
    {
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (nowSelectedNum == chess[i][j].text().toInt()) {

                    chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                            "font: 14pt \"Microsoft YaHei UI\";\n"
                                                            "color: #ffffff;"));
                }
            }
        }
        /*如果点击已经选中的值，则清0*/
        if (nowSelectedNum == aimmedNum)
            nowSelectedNum = 0;
        else
            nowSelectedNum = aimmedNum;
    }
}



void ChessBoardSceen::initChessboard()
{
    sudokuPower = new MySudoku(HardLevel::easy);
    nowGameHardLevel = HardLevel::easy;
    MySudoku & shortNameSudoku = *sudokuPower;
    QGridLayout* chessboardLayout = new QGridLayout;
    QString temp;

    for(int i = 0; i < 9; ++i)
    {
        everyNumCorrectCount[i] = 0;
    }

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            chess[i][j].setFixedSize(40, 40);
            chessboardLayout->addWidget(&chess[i][j], i, j);
            chess[i][j].setAccessibleName(QString::number(i * 10 + j));//设置可以定位棋盘的别名
            chess[i][j].setText(temp.setNum(shortNameSudoku[i][j]));
            if (0 == shortNameSudoku[i][j])
            {
                ++emptyNum;
                everyNumCorrectCount[shortNameSudoku.truth[i][j]-1]++;//记录下每个数有多少个空白格子，计分用
                chess[i][j].setText("");
            }
            connect(&chess[i][j], SIGNAL(clicked()), this, SLOT(chessBoardClicked()));

            chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                    "font: 14pt \"Microsoft YaHei UI\";\n"
                                                    "color: #ffffff;"));
        }
    }
    chessboardLayout->setMargin(10);
    chessboardLayout->setVerticalSpacing(2);
    chessboardLayout->setHorizontalSpacing(2);
    for (int i = 0; i < 9; ++i)
    {
        chessboardLayout->setColumnStretch(i, 0);
        chessboardLayout->setRowStretch(i, 0);
    }
    this->setLayout(chessboardLayout);
    nowSelectedNum = 0;//游戏重新开始，高亮选中的值置0
}


void ChessBoardSceen::keyPressEvent(QKeyEvent *event)
{
    QString temp(event->key());
    int n = onPressingBoard;
    int x_Pos = n / 10, y_Pos = n % 10;
    vvint & chessTruth = sudokuPower->truth;

    if(temp == "H")
        temp.setNum(chessTruth[x_Pos][y_Pos]);

    if (n == -1 || chess[x_Pos][y_Pos].text() != "")//如果已经填入则不能再输入 //没有选中空白格子
    {
        return;
    }

    if (chessTruth[x_Pos][y_Pos] == temp.toInt())//如果输入正确则填入
    {
        addOneWrite(temp);
    }
    else
    {    //错误统计加一
        addOneWrong();
    }
}


void ChessBoardSceen::addOneWrite(QString temp)
{
    int n = onPressingBoard;
    int x_Pos = n / 10, y_Pos = n % 10;
    chess[x_Pos][y_Pos].setText(temp);
//计分
    if(--everyNumCorrectCount[temp.toInt()-1] == 0)
    {
        score+= (3600 - timerCount)/*3600秒减当前秒数*/ * everyNumCorrectCount[temp.toInt()-1];/*当前完成的数字*/
        score+=10000;
        qDebug()<<temp.toInt()<<" score: "<<score;
    }

    score += 200;
    --emptyNum;
    if(emptyNum == 0)   //胜利
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox ::question(this, tr("你赢了！！！"),"是否重新开始？",QMessageBox::Ok|QMessageBox::Cancel);
        if(reply == QMessageBox::Ok)
        {
            emit(beginningNewGame(nowGameHardLevel));
        }
    }
}

void ChessBoardSceen::addOneWrong()
{

    if (wrongTime++ > 3)  //最多错三次
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox ::question(this, tr("你输了！！！"),"是否重新开始？",QMessageBox::Ok|QMessageBox::Cancel);
        if(reply == QMessageBox::Ok)
        {
            emit(beginningNewGame(nowGameHardLevel));
        }
        return;
    }
}


void ChessBoardSceen::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId)
    {
        ++timerCount;
        //  qDebug() << timerId;
    }
}
