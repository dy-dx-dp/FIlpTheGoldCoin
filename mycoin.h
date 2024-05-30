#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin();
    MyCoin(QString img,int x, int y, bool flag);
    bool getFlag() const;
    void setFlag(bool newFlag);
    void FlipTheCoin();    //翻转硬币


private:
    QTimer *goldTimer;     //金币定时器
    QTimer *sliverTimer;   //银币定时器
    int goldCoinFrames;
    int sliverCoinFrames;
    int x;
    int y;
    bool flag;

private slots:

};

#endif // MYCOIN_H
