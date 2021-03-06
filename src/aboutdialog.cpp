#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QVBoxLayout>
#include <QMouseEvent>

#include "publictitlebar.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
#if 1
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
#endif
    publicTitleBar *titleBar = new publicTitleBar;
    titleBar->setCloseBtnBg("/new/prefix1/closeBtn");
    titleBar->setTitle("解释说明");
    titleBar->setIcon("/new/prefix1/loginLogo");

    QVBoxLayout* upLayout = new QVBoxLayout;
    upLayout->setContentsMargins(0, 0, 0, 0);
    upLayout->setSpacing(0);
    upLayout->addWidget(titleBar);
    upLayout->addStretch();
    ui->up->setLayout(upLayout);

    connect(titleBar, SIGNAL(clickedCloseButton()), this, SLOT(close()));

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::mousePressEvent(QMouseEvent *event)
{
    mIsMousePressed = true;
    if (event->button() == Qt::LeftButton)
    {
        mLastDragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void AboutDialog::mouseReleaseEvent(QMouseEvent *)
{
    mIsMousePressed = false;
}

void AboutDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (mIsMousePressed) {
            this->move(event->globalPos() - mLastDragPos);
            event->accept();
        }
    }
}
