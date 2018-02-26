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
    void chessBoardClicked();
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QPushButton chess[9][9];
    MySudoku *chessBoard;//生成的数独数字
    int nowSelectedNum;
    int onPressingBoard;
private:
    void highLightSelectedButtons(int aimmedNum);
    void resetChessboard(MySudoku &chessB);
    void addOneWrong();
};

#endif // MAINWINDOW_H
