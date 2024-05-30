#include "levelsense.h"
#include "ui_levelsense.h"

LevelSense::LevelSense(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelSense)
{
    ui->setupUi(this);
}

LevelSense::LevelSense(int level, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelSense)
{
    ui->setupUi(this);
    setFixedSize(300,520);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, pix.scaled(this->width(),this->height()));
    this->setPalette(palette);

    this->level = level;

    //设置翻金币场景
    for(int i = 0;i<4;i++){
        for(int j=0;j<4;j++){
            QPixmap pix(":/res/BoardNode.png");
            QLabel *label_coin = new QLabel(this);
            label_coin->setGeometry(0,0,pix.width(),pix.height());
            label_coin->setPixmap(pix);
            label_coin->move(50+i*50,180+j*50);
        }
    }

    QPixmap pixmap(":/res/LevelCompletedDialogBg.png");
    QLabel *label_success = new QLabel(this);
    label_success->setGeometry(0,0,pixmap.width(),pixmap.height());
    label_success->setPixmap(pixmap);
    label_success->move(this->width()*0.5-pixmap.width()*0.5,-pixmap.height());

    //设置金币
    QString coinPath;
    dataConfig config;
    for(int i = 0;i<4;i++){
        for(int j=0;j<4;j++){
            levelMsg[i][j] = config.mData[this->level][i][j];
            if(levelMsg[i][j]==1)
                coinPath = ":/res/Coin0001.png";
            else
                coinPath = ":/res/Coin0008.png";
            MyCoin *coin = new MyCoin(coinPath,i,j,levelMsg[i][j]);
            coins[i][j] = coin;
            coin->setParent(this);
            coin->move(54+i*50,184+j*50);
            connect(coin,&QPushButton::clicked,this,[=](){
                coin->FlipTheCoin();
                QTimer::singleShot(300,this,[=](){
                    if(0<=(i-1) && (i-1)<4){
                        coins[i-1][j]->FlipTheCoin();
                    }
                    if(0<=(i+1) && (i+1)<4){
                        coins[i+1][j]->FlipTheCoin();
                    }
                    if(0<=(j-1) && (j-1)<4){
                        coins[i][j-1]->FlipTheCoin();
                    }
                    if(0<=(j+1) && (j+1)<4){
                        coins[i][j+1]->FlipTheCoin();
                    }

                    //判断是否胜利
                    isWin = true;
                    for(int k = 0;k<4;k++){
                        for(int q = 0;q<4;q++){
                            if(!coins[k][q]->getFlag()){
                                isWin = false;
                                break;
                            }
                        }
                    }
                    if(isWin){
                        for(int k = 0;k<4;k++){
                            for(int q = 0;q<4;q++){
                                    coins[k][q]->setEnabled(false);
                            }
                        }

                        QPropertyAnimation *animation1 =  new QPropertyAnimation(label_success,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(label_success->x(),label_success->y(),label_success->width(),label_success->height()));
                        animation1->setEndValue(QRect(label_success->x(),label_success->y()+114,label_success->width(),label_success->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                    }
                });
            });
        }
    }

    MyPushButton *btn_back = new MyPushButton(":/res/BackButton.png");
    btn_back->setParent(this);
    btn_back->move(this->width()-btn_back->width(),this->height()-btn_back->height());
    connect(btn_back,&QPushButton::clicked,this,[=](){
        this->hide();
        emit back();      //发送返回信号
    });

    QLabel *label_level = new QLabel(this);
    label_level->setText(QString::asprintf("LEVEL：%d",level));
    QFont font("黑体", 30); // 字体为黑体，大小为20
    // 设置标签的字体
    label_level->setFont(font);
    label_level->move(30,this->height()-label_level->height()-20);
}

LevelSense::~LevelSense()
{
    delete ui;
}

void LevelSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制左上角图标
    QPixmap backgroundIcon(":/res/Title.png"); // 替换为您的背景图片路径
    painter.drawPixmap(10,30, backgroundIcon.scaled(backgroundIcon.width()*0.5,backgroundIcon.height()*0.5));
}
