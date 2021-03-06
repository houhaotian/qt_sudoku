#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class loginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

protected:
    void setFlatButton(QPushButton *btn, QString normalColor,
                       QString normalTextColor, QString hoverColor,
                       QString hoverTextColor, QString pressedColor, QString pressedTextColor
                       );

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private slots:

    void on_startButton_clicked();
    void on_aboutButton_clicked();

private:
    Ui::loginDialog *ui;
    bool mIsMousePressed;
    QPoint mLastDragPos;

};

#endif // LOGINDIALOG_H
