#include "mycoin.h"

MyCoin::MyCoin()
{

}

MyCoin::MyCoin(QString img,int x, int y, bool flag)
{
    goldCoinFrames = 1;
    sliverCoinFrames = 8;
    this->x = x;
    this->y = y;
    this->flag = flag;
    goldTimer = new QTimer(this);
    sliverTimer = new QTimer(this);
    QPixmap pix;
    if(!pix.load(img)){
        qDebug()<<"图片加载失败！";
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(QIcon(pix));
    this->setIconSize(pix.size());
    connect(goldTimer,&QTimer::timeout,this,[=](){
        QPixmap pix(QString::asprintf(":/res/Coin000%d.png",goldCoinFrames));
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(QIcon(pix));
        this->setIconSize(pix.size());
        goldCoinFrames++;
        if(goldCoinFrames>8){
            goldCoinFrames = 1;
            goldTimer->stop();
        }
    });

    connect(sliverTimer,&QTimer::timeout,this,[=](){
        QPixmap pix(QString::asprintf(":/res/Coin000%d.png",sliverCoinFrames));
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(QIcon(pix));
        this->setIconSize(pix.size());
        sliverCoinFrames--;
        if(sliverCoinFrames<1){
            sliverCoinFrames = 8;
            sliverTimer->stop();
        }
    });
}

void MyCoin::FlipTheCoin()
{

    if(flag){
        goldTimer->start(30);
        flag = false;
    }

    else{
        sliverTimer->start(30);
        flag = true;
    }
}

bool MyCoin::getFlag() const
{
    return flag;
}

void MyCoin::setFlag(bool newFlag)
{
    flag = newFlag;
}


