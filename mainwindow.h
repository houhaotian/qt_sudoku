#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QAction>



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
    void clickedBeginNewGameButton(int);
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
    MySudoku *sudokuPower;//生成的数独数字
    QLabel *wrongLabel[3];
    QAction * hardMenu[4];
    QLabel *score;

    static int nowSelectedNum;
    static int onPressingBoard;
    static int wrongTime;
    static int nowGameHardLevel;
    static int nowEmptyButtonX;
    static int nowEmptyButtonY;
    static int emptyNum;

private:
    void initSudokuChessBoard();
    void putOnMenuItem();
    void putOnScoreLabel();
    void highLightSelectedButtons(int aimmedNum);
    void resetChessboard(MySudoku &chessB);
    void addOneWrong();
};

#endif // MAINWINDOW_H
