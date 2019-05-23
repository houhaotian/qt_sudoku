#include "logindialog.h"
#include "ui_logindialog.h"
#include "publicTitleBar.h"
#include "aboutdialog.h"


#include <QMouseEvent>
#include <QVBoxLayout>



LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    publicTitleBar *titleBar = new publicTitleBar();
    titleBar->setCloseBtnBg("/new/prefix1/closeBtn");
    titleBar->setTitle(QStringLiteral("我的小数独"));
    titleBar->setIcon("/new/prefix1/loginLogo");


    QVBoxLayout* upLayout = new QVBoxLayout;
    upLayout->setContentsMargins(0, 0, 0, 0);
    upLayout->setSpacing(0);
    upLayout->addWidget(titleBar);
    upLayout->addStretch();
    ui->up->setLayout(upLayout);

    setFlatButton(ui->startButton, "#3366CC", "#242424", "#f25353", "#ffffff", "#ce4545", "#ffffff");
    setFlatButton(ui->aboutButton, "#3366CC", "#242424", "#f25353", "#ffffff", "#ce4545", "#ffffff");
    connect(titleBar, SIGNAL(clickedCloseButton()), this, SLOT(close()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}



void LoginDialog::setFlatButton(QPushButton *btn,
                           QString normalColor,
                           QString normalTextColor,
                           QString hoverColor,
                           QString hoverTextColor,
                           QString pressedColor,
                           QString pressedTextColor
                           )
{
    QStringList qss;
    /*border-radius:6px;*/
    qss.append(QString("QPushButton{border-style:none;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

void LoginDialog::on_startButton_clicked()
{
    accept();
}

void LoginDialog::on_aboutButton_clicked()
{
    AboutDialog abtDlg;
    abtDlg.exec();
}


void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    mIsMousePressed = true;
    if (event->button() == Qt::LeftButton)
    {
        mLastDragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mIsMousePressed = false;
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (mIsMousePressed) {
            this->move(event->globalPos() - mLastDragPos);
            event->accept();
        }
    }
}
