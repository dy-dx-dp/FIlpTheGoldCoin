#include "mypushbutton.h"

MyPushButton::MyPushButton()
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImg = normalImg;
    this->pressImg = pressImg;
    QPixmap pixmap;
    if(!(pixmap.load(normalImg))){
        qDebug()<<"加载图片失败！";
        return;
    }

    //设置按钮大小为图片大小
    this->setFixedSize(pixmap.width(),pixmap.height());

    //设置按钮无边框
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置按钮的icon
    this->setIcon(QIcon(normalImg));

    //设置icon大小为图片大小
    this->setIconSize(pixmap.size());

    //this->show();
}

void MyPushButton::dumpAnimation()
{
    QPropertyAnimation *animationDown = new QPropertyAnimation(this, "geometry");

    //设置动画时间间隔
    animationDown->setDuration(200);


    animationDown->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animationDown->setEndValue(QRect(this->x(),this->y()+15,this->width(),this->height()));

    animationDown->setEasingCurve(QEasingCurve::OutBounce);
    //开始动画
    animationDown->start();

    this->setEnabled(false);
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true); // 设置定时器仅触发一次
    timer->start(200); // 设置定时器间隔为500毫秒

    // 连接定时器的timeout信号到槽函数
    QObject::connect(timer, &QTimer::timeout, [=]() {
        QPropertyAnimation *animationUp = new QPropertyAnimation(this, "geometry");
        //设置动画时间间隔
        animationUp->setDuration(200);

        animationUp->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        animationUp->setEndValue(QRect(this->x(),this->y()-15,this->width(),this->height()));

        animationUp->setEasingCurve(QEasingCurve::OutBounce);
        //开始动画
        animationUp->start();
        this->setEnabled(true);
    });

}

void MyPushButton::dumpAnimationUp()
{
    /*QPropertyAnimation *animationUp = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animationUp->setDuration(200);

    animationUp->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animationUp->setEndValue(QRect(this->x(),this->y()-15,this->width(),this->height()));

    animationUp->setEasingCurve(QEasingCurve::OutBounce);
    //开始动画
    animationUp->start();*/

}

