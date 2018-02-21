#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


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


protected:
     virtual void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;


    QPushButton chess[9][9];

};

#endif // MAINWINDOW_H
