#ifndef PUBLICTITLEBAR_H
#define PUBLICTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>



class publicTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit publicTitleBar(QWidget *parent = nullptr);
    void setTitle(const QString& text);
    //   void setTextColor(const QColor &color);
    void setIcon(const QString &imgPath);
    void setCloseBtnBg(const QString &imgPath);
    //  void setBgColor(const QColor& color);
signals:
    void clickedCloseButton();
public slots:

private:
    QLabel* mIcon;
    QLabel* mTitle;
    QToolButton* mClose;
};

#endif // PUBLICTITLEBAR_H
