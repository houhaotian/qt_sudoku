#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


#include "mySudoku/mysudoku.h"
#include "mySudoku/hardlevel.h"


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
    void newGameClicked();
protected:
     virtual void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QPushButton chess[9][9];
    MySudoku *chessBoard;
};

#endif // MAINWINDOW_H
