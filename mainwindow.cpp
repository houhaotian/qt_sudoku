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
#if 1
   chessBoard = new MySudoku(HardLevel::master);
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
         //   connect(b[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));

            chess[i][j].setStyleSheet(QLatin1String("background-color: #3366CC;\n"
                                        "font: 14pt \"Microsoft YaHei UI\";\n"
                                        "color: #ffffff;"));
        }
    }
    cboardLayout->setMargin(2);
    cboardLayout->setVerticalSpacing(2);
    cboardLayout->setHorizontalSpacing(2);
    for(int i = 0; i < 9; ++i)
    {
        cboardLayout->setColumnStretch(i,0);
        cboardLayout->setRowStretch(i,0);
    }
    ui->centralWidget->setLayout(cboardLayout);
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
        //    painter.drawLine( x1+1 ,y1+2+bm,x1+1,y2+bm );
        painter.drawLine(x1 + 1, y1 + 2, x1 + 1, y2);

    }
    for (int i = 3; i < 8; i += 3)
    {
        int y1 = (chess[i][0].geometry().top() + chess[i - 1][0].geometry().bottom()) / 2;
        int x1 = chess[i][0].geometry().left();
        int x2 = chess[i][8].geometry().right();
        //  painter.drawLine( x1+2 ,y1+1+bm,x2-2,y1+1+bm );
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
    QAction *incomeBtn = qobject_cast<QAction*>(sender());
    temp = incomeBtn->text();//获得传过来的难度等级
    int incomeLevel;
    for(int i=0;i<4;++i)
    {
        if(temp == str_hardclass[i])
           incomeLevel = i;
    }
    chessBoard = new MySudoku(incomeLevel);
    MySudoku & chessB = *chessBoard;

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            chess[i][j].setText(temp.setNum(chessB[i][j]));
            if(0 == chessB[i][j])
            {
                chess[i][j].setText("");
            }
            //   connect(b[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));
        }
    }
}
