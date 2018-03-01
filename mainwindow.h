#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include<QVector>


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
    void emitStartSignal();
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui; 
    QLabel *wrongLabel[3];
    QAction * hardMenu[4];
    QLabel *score;
    ChessBoardSceen *chessBoardWidget;
private:
    void putOnMenuItem();
    void putOnScoreLabel();
    void putOnChessBoardWidget();
};

#endif // MAINWINDOW_H
