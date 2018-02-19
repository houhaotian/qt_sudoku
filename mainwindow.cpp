#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>



#include "publictitlebar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    publicTitleBar *titleBar = new publicTitleBar;
    titleBar->setCloseBtnBg("/new/prefix1/closeBtn");
    titleBar->setTitle("享用游戏吧");
    titleBar->setIcon("/new/prefix1/loginLogo");

    QVBoxLayout* upLayout = new QVBoxLayout;
    upLayout->setContentsMargins(0, 0, 0, 0);
    upLayout->setSpacing(0);
    upLayout->addWidget(titleBar);
    upLayout->addStretch();
    ui->up->setLayout(upLayout);


    QGridLayout* cboardLayout = new QGridLayout;
    QString temp;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            chess[i][j].setMinimumSize(30, 30);
         //   b[i][j]->setFont(ft2);
            cboardLayout->addWidget(&chess[i][j], i, j);
            chess[i][j].setAccessibleName(QString::number(i * 10 + j));

            chess[i][j].setText(temp.setNum(j));
         //   connect(b[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));
            chess[i][j].setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            chess[i][j].setStyleSheet("background-color: #3366CC;");
        }
    }



    cboardLayout->setMargin(1);
    cboardLayout->setVerticalSpacing(1);
    cboardLayout->setHorizontalSpacing(1);
    for(int i = 0; i < 9; ++i)
    {
        cboardLayout->setColumnStretch(i,1);
        cboardLayout->setRowStretch(i,1);
    }
    ui->down->setLayout(cboardLayout);

















    connect(titleBar, SIGNAL(clickedCloseButton()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}














void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mIsMousePressed = true;
    if (event->button() == Qt::LeftButton)
    {
        mLastDragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    mIsMousePressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (mIsMousePressed) {
            this->move(event->globalPos() - mLastDragPos);
            event->accept();
        }
    }
}
