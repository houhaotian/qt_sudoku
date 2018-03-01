#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QPainter>
#include <QString>
#include <QMessageBox>
#include <QDebug>

#include "publictitlebar.h"
#include "aboutdialog.h"


::QString stringHardLevel[4] = { "简单","中等","困难","地狱" };


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("我的小数独"));

    //添加棋盘
    putOnChessBoardWidget();
    //添加菜单栏
    putOnMenuItem();
    //添加score栏
    putOnScoreLabel();
    //添加错误图片栏
    putOnWrongLabelContainer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::putOnMenuItem()
{
    /*菜单栏新游戏*/
    for (int i = 0; i < 4; ++i)
    {
        hardMenu[i] = new QAction(stringHardLevel[i]);
        ui->newGame->addAction(hardMenu[i]);
        connect(hardMenu[i], SIGNAL(triggered()), this, SLOT(emitStartSignal()));
    }
    /*菜单栏其它*/
    QAction *aboutMenu = new QAction("关于");
    ui->others->addAction(aboutMenu);
    connect(aboutMenu, SIGNAL(triggered()), this, SLOT(onAboutTriggered()));
}

void MainWindow::putOnScoreLabel()
{
    //score添加
    score = new QLabel(ui->left);
    score->setObjectName(QStringLiteral("score"));
    score->setGeometry(QRect(10, 50, 54, 21));
    QFont font1;
    font1.setFamily(QStringLiteral("Consolas"));
    font1.setPointSize(11);
    font1.setBold(true);
    font1.setWeight(75);
    score->setFont(font1);
    score->setStyleSheet(QStringLiteral("color: rgb(245, 245, 245);r"));
    score->setNum(0);//清空得分
    connect(chessBoardWidget, &ChessBoardSceen::playerHitPoint, this, &getScoreFromChessBoardChild);
}

void MainWindow::putOnChessBoardWidget()
{
    chessBoardWidget = new ChessBoardSceen;
    QHBoxLayout *templayout = new QHBoxLayout;
    templayout->addWidget(chessBoardWidget);
    ui->right->setLayout(templayout);
}

void MainWindow::putOnWrongLabelContainer()
{
    QFont font1;
    font1.setFamily(QStringLiteral("Consolas"));
    font1.setPointSize(11);
    font1.setBold(true);
    font1.setWeight(75);

    upHLayout = new QHBoxLayout(ui->up);
    wrongItem = new QLabel("错误:");
    wrongItem->setFont(font1);
    wrongItem->setStyleSheet("color:#ffffff;");

    wrongLabelContainer = new QWidget;
    upHLayout->addWidget(wrongItem);
    upHLayout->addWidget(wrongLabelContainer);
    upHLayout->setStretch(1,6);
    wrongLabelContainerLayout = new QHBoxLayout;
    wrongLabelContainerLayout->setAlignment(Qt::AlignLeft);
    wrongLabelContainer->setLayout(wrongLabelContainerLayout);

    connect(chessBoardWidget, &ChessBoardSceen::playerHitWrong, this, &monitorWrongNum);
    connect(chessBoardWidget, &ChessBoardSceen::playerHitReStart, this, &monitorRestartGame);

}

void MainWindow::monitorWrongNum()
{
    int i = chessBoardWidget->getWrongTime();
    if(i > 3)
    {
        //游戏失败
        //不要弹出窗口
        return;
    }
    qDebug()<<i;
    QLabel *wrongLabel = new QLabel;

    wrongLabel->setStyleSheet(QStringLiteral("image: url(:/new/prefix1/mainico);"));
    wrongLabel->setMinimumSize(40,40);
    wrongLabel->setVisible(1);
    wrongLabelContainerLayout->addWidget(wrongLabel);

}

void MainWindow::paintEvent(QPaintEvent *)
{
    //    int bm=ui->menuBar->geometry().bottom();
    QPainter painter(this);
    QPen penType;
    penType.setWidth(3);
    penType.setColor(Qt::darkBlue);
    painter.setPen(penType);

    int x0 = (ui->down->x()) + 90;
    int y0 = ui->down->y() + 38;
    //  painter.drawLine(x0, y0, x0, 400);

    int x1 = x0 + 3* 40 +9;
    painter.drawLine(x1, y0, x1 , 480);
    x1 += 3 * 40 + 7;
    painter.drawLine(x1 , y0, x1 , 480);
    int y1 = y0 + 3* 40 + 5;
    painter.drawLine(x0 , y1, 475 , y1);
    y1 += 3* 40 + 7;
    painter.drawLine(x0 , y1, 475 , y1);

#if 0
    for (int i = 3; i < 8; i += 3)
    {
        int x1 = (chess[0][i].geometry().left() + chess[0][i - 1].geometry().right()) / 2;
        int y1 = chess[0][i].geometry().top();
        int y2 = chess[8][i].geometry().bottom();

        painter.drawLine(x1, y1, x1 , y2);
    }
    for (int i = 3; i < 8; i += 3)
    {
        int y1 = (chess[i][0].geometry().top() + chess[i - 1][0].geometry().bottom()) / 2;
        int x1 = chess[i][0].geometry().left();
        int x2 = chess[i][8].geometry().right();

        painter.drawLine(x1, y1, x2 , y1);
    }
#endif
}

void MainWindow::onAboutTriggered()
{
    AboutDialog abtDlg;
    abtDlg.exec();
}

void MainWindow::emitStartSignal()
{
    QAction * senderAction = qobject_cast<QAction *>(sender());
    QString senderName = senderAction->text();

    for(int x = 0; x < 4; ++x)
    {
        if(senderName == stringHardLevel[x])
        {
          //  qDebug() << x;
            emit(chessBoardWidget->beginningNewGame(x));
            return;
        }
    }
}

void MainWindow::getScoreFromChessBoardChild()
{
    score->setNum(chessBoardWidget->getScore());
}


void MainWindow::monitorRestartGame()
{
    score->setNum(0);
    //删掉wrongLabelContainer
    delete wrongLabelContainer;
    wrongLabelContainer = new QWidget;
    upHLayout->addWidget(wrongLabelContainer);
    upHLayout->setStretch(1,6);
    wrongLabelContainerLayout = new QHBoxLayout;
    wrongLabelContainerLayout->setAlignment(Qt::AlignLeft);
    wrongLabelContainer->setLayout(wrongLabelContainerLayout);
}
