#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QPropertyAnimation>
#include <QTimer>
#include <QThread>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton();
    MyPushButton(QString normalImg,QString pressImg = "");
    void dumpAnimation();
    void dumpAnimationUp();

private:
    QString normalImg;
    QString pressImg;

private slots:

};

#endif // MYPUSHBUTTON_H
