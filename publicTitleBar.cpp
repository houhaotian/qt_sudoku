#include "publicTitleBar.h"
#include <QHBoxLayout>




publicTitleBar::publicTitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(20);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(5, 0, 0, 0);
    setLayout(layout);

    mClose = new QToolButton(this);
    mClose->setFixedSize(36, 20);
    mClose->setToolTip("关闭");
    mClose->setFocusPolicy(Qt::NoFocus);

    mTitle = new QLabel("hello world", this);

    mIcon = new QLabel(this);
    mIcon->setFixedSize(20, 20);

    layout->addWidget(mIcon);
    layout->addSpacing(8);
    layout->addWidget(mTitle);
    layout->addWidget(mClose);

    connect(mClose, SIGNAL(clicked()), this, SIGNAL(clickedCloseButton()));

}



void publicTitleBar::setTitle(const QString &text)
{
    mTitle->setText(text);
}

void publicTitleBar::setIcon(const QString &imgPath)
{
    QString qss = "border-image: url(:";
    qss += imgPath;
    qss += ");";
    mIcon->setStyleSheet(qss);
}

void publicTitleBar::setCloseBtnBg(const QString &imgPath)
{
    QString qss;
    qss.append(QString("QToolButton{border-style:none;background:url(:%1);background-position:left;}").arg(imgPath));
    qss.append(QString("QToolButton:hover{border-style:none;background:url(:%1);background-position:center;}").arg(imgPath));
    qss.append(QString("QToolButton:pressed{border-style:none;background:url(:%1);background-position:right;}").arg(imgPath));
    mClose->setStyleSheet(qss);
}
