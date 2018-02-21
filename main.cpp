#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <logindialog.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/loginLogo"));


    LoginDialog* login = new LoginDialog;
    login->move((QApplication::desktop()->width() - login->width()) / 2, (QApplication::desktop()->height() - login->height()) / 2);
    login->exec();

    if (QDialog::Accepted == login->result())
    {
        MainWindow w;
        w.show();
        delete login;
        return a.exec();
    }
    return 0;
}
