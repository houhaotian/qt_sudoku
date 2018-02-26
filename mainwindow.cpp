#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QPainter>
#include <QString>

#include "publictitlebar.h"
#include "aboutdialog.h"

::QString str_hardclass[4]={"简单","中等","困难","地狱"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("我的小数独"));

#if 1
    chessBoard = new MySudoku(HardLevel::easy);
    MySudoku & chessB=*chessBoard;
    QGridLayout* cboardLayout = new QGridLayout;
    QString temp;

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            chess[i][j].setFixedSize(30, 30);
            cboardLayout->addWidget(&chess[i][j], i, j);
            chess[i][j].setAccessibleName(QString::number(i * 10 + j));

            chess[i][j].setText(temp.setNum(chessB[i][j]));
            if(0 == chessB[i][j])
            {
                chess[i][j].setText("");
            }
            connect(&chess[i][j], SIGNAL(clicked()), this, SLOT(chessBoardClicked()));

            chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                    "font: 14pt \"Microsoft YaHei UI\";\n"
                                                    "color: #ffffff;"));
        }
    }
    nowSelectedNum = 0;//游戏重新开始
    cboardLayout->setContentsMargins(40, 0, 10, 10);
    cboardLayout->setVerticalSpacing(2);
    cboardLayout->setHorizontalSpacing(2);
    for(int i = 0; i < 9; ++i)
    {
        cboardLayout->setColumnStretch(i,0);
        cboardLayout->setRowStretch(i,0);
    }
    ui->right->setLayout(cboardLayout);
#endif


    /*菜单栏新游戏*/
    for(int i = 0; i < 4; ++i)
    {
        QAction *hardMenu = new QAction(str_hardclass[i]);
        ui->newGame->addAction(hardMenu);
        connect(hardMenu, SIGNAL(triggered()), this, SLOT(newGameClicked()));
    }
    /*菜单栏其它*/
    QAction *aboutMenu = new QAction("关于");
    ui->others->addAction(aboutMenu);
    connect(aboutMenu, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::paintEvent(QPaintEvent *)
{
    //    int bm=ui->menuBar->geometry().bottom();
    QPainter painter(this);
    QPen penType;
    penType.setWidth(3);
    penType.setColor(Qt::red);
    painter.setPen(penType);
    /*   painter.drawLine(ui->centralWidget->geometry().x(),ui->centralWidget->geometry().y(),
                         ui->centralWidget->geometry().x()+100,ui->centralWidget->geometry().y()+100
                         );
    */

    for (int i = 3; i < 8; i += 3)
    {
        int x1 = (chess[0][i].geometry().left() + chess[0][i - 1].geometry().right()) / 2;
        int y1 = chess[0][i].geometry().top();
        int y2 = chess[8][i].geometry().bottom();

        painter.drawLine(x1 + 1, y1 + 2, x1 + 1, y2);

    }
    for (int i = 3; i < 8; i += 3)
    {
        int y1 = (chess[i][0].geometry().top() + chess[i - 1][0].geometry().bottom()) / 2;
        int x1 = chess[i][0].geometry().left();
        int x2 = chess[i][8].geometry().right();

        painter.drawLine(x1 + 2, y1 + 1, x2 - 2, y1 + 1);
    }

}


void MainWindow::onAboutTriggered()
{
    AboutDialog abtDlg;
    abtDlg.exec();
}

void MainWindow::newGameClicked()
{
    delete chessBoard;

    QString temp;
    QAction *incomeBtn = qobject_cast<QAction *>(sender());
    temp = incomeBtn->text();//获得传过来的难度等级
    int incomeLevel;
    for(int i = 0; i < 4; ++i) {
        if(temp == str_hardclass[i])
            incomeLevel = i;
    }
    chessBoard = new MySudoku(incomeLevel);
    MySudoku & chessB = *chessBoard;

    resetChessboard(chessB);
    nowSelectedNum = 0;//游戏重新开始
}

void MainWindow::resetChessboard(MySudoku & chessB)
{
    QString temp;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            chess[i][j].setText(temp.setNum(chessB[i][j]));
            chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                    "font: 14pt \"Microsoft YaHei UI\";\n"
                                                    "color: #ffffff;"));
            if(0 == chessB[i][j])
            {
                chess[i][j].setText("");
            }
        }
    }
}

void MainWindow::chessBoardClicked()
{
    QPushButton * btn = qobject_cast<QPushButton *>(sender());
    int n = btn->accessibleName().toInt();
    int i = n/10,j = n%10;
    int x_t = i, y_t = j;
    int aimmedNum = chess[x_t][y_t].text().toInt();
    if(aimmedNum == 0)
    {
        onPressingBoard = n;
        //   chess[x_t][y_t].setStyleSheet(QLatin1String("background-color: #ffaa7f;\n"
        //                                         "font: 14pt \"Microsoft YaHei UI\";\n"
        //                                       "color: #ffffff;"));
        return;
    }
    else/*高亮选中的值*/
    {
        highLightSelectedButtons(aimmedNum);
    }
}

void MainWindow::highLightSelectedButtons(int aimmedNum)
{
    /*高亮选中数字*/
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(aimmedNum == chess[i][j].text().toInt()){
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
        for(int i = 0; i < 9; ++i)
        {
            for(int j = 0; j < 9; ++j)
            {
                if(nowSelectedNum == chess[i][j].text().toInt()){

                    chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                                            "font: 14pt \"Microsoft YaHei UI\";\n"
                                                            "color: #ffffff;"));
                }
            }
        }
        /*如果点击已经选中的值，则清0*/
        if (nowSelectedNum == aimmedNum)
        {
            nowSelectedNum = 0;
            return;
        }
        else
        nowSelectedNum = aimmedNum;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    QString temp(event->key());
    int n = onPressingBoard;
    int i = n/10,j = n%10;
    int x_t = i, y_t = j;
    vvint & chessB = chessBoard->truth;
    static int score = 0;
    static int wrongtime = 0;
    if(chessB[x_t][y_t] == temp.toInt())//如果输入正确则填入
    {
        chess[x_t][y_t].setText(temp);
        score += 200;
        ui->score->setNum(score);
    }
    else
    {    //错误统计加一
        addOneWrong();
        wrongtime++;
    }
}

void MainWindow::addOneWrong()
{
    QLabel * wrongLabel = new QLabel(ui->up);
    wrongLabel->setGeometry(QRect(ui->up->x()+10, ui->up->y()+10, 91, 61));
    wrongLabel->setStyleSheet(QStringLiteral("image: url(:/new/prefix1/mainico);"));

}
