#include "choosesense.h"
#include "ui_choosesense.h"

ChooseSense::ChooseSense(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseSense)
{
    ui->setupUi(this);
    setFixedSize(300, 520);
    setWindowTitle("金币翻转小游戏");
    QPixmap background(":/res/OtherSceneBg.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->width(),this->height()));
    this->setPalette(palette);

    for(int i = 0;i < 20; i++){
        MyPushButton *btn_level = new MyPushButton(":/res/LevelIcon.png");
        btn_level->setParent(this);
        btn_level->move(15+i%4*70,120+i/4*70);

        QLabel *label = new QLabel(this);
        label->setFixedSize(btn_level->width(),btn_level->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignCenter);
        label->move(15+i%4*70,120+i/4*70);
        //设置鼠标穿透，标签将不再响应鼠标事件，而是允许鼠标事件穿透到标签下方的其他控件或窗口。
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(btn_level,&QPushButton::clicked,this,[=](){
            LevelSense *levelSense = new LevelSense(i+1);
            this->hide();
            levelSense->show();
            connect(levelSense,&LevelSense::back,this,[=](){
                this->show();
                levelSense->close();
                delete levelSense;
            });
        });
    }

    //设置返回按钮
    MyPushButton *btn_close = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn_close->setParent(this);
    btn_close->move(this->width()-btn_close->width(),this->height()-btn_close->height());

    connect(btn_close,&QPushButton::clicked,this,[=](){
        emit chooseSenseBack();
        this->hide();
    });
}

ChooseSense::~ChooseSense()
{
    delete ui;
}

void ChooseSense::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制左上角图标
    QPixmap backgroundIcon(":/res/Title.png"); // 替换为您的背景图片路径
    painter.drawPixmap(10,5, backgroundIcon.scaled(backgroundIcon.width(),backgroundIcon.height()));
}
