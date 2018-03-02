#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include<QVector>
#include <QBoxLayout>


#include "mySudoku/mysudoku.h"
#include "mySudoku/hardlevel.h"
#include "chessboardsceen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

private slots:
    void onAboutTriggered();
    void emitStartSignal();//处理菜单栏开始游戏按键对应操作
    void getScoreFromChessBoardChild();//监控得分
    void monitorWrongNum();//监控错误
    void monitorRestartGame();//如果重新开始游戏要清空label,score

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    QAction * hardMenu[4];//菜单栏四个开始按钮
    QLabel *score;  //显示得分的label
    ChessBoardSceen *chessBoardWidget;  //棋盘子控件
    QLabel *timeLabel;  //显示得分的label

    /*上边栏子控件*/
    QWidget * wrongLabelContainer;
    QHBoxLayout *wrongLabelContainerLayout;
    QHBoxLayout *upHLayout;
    QLabel * wrongItem;

    int timerId;    //设置定时器时间为1s
    double timerCount;  //记录总时间

private:
    void putOnMenuItem();
    void putOnScoreLabel();
    void putOnChessBoardWidget();
    void putOnWrongLabelContainer();
};

#endif // MAINWINDOW_H
