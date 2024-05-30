#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(300, 520);
    setWindowTitle("金币翻转");
    QPixmap background(":/res/PlayLevelSceneBg.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->width(),this->height()));
    this->setPalette(palette);

    MyPushButton *btn_start = new MyPushButton(":/res/MenuSceneStartButton.png");
    btn_start->setParent(this);
    btn_start->move(this->width()*0.5-btn_start->width()*0.5,this->height()*0.7);

    ChooseSense *chooseSense = new ChooseSense();
    connect(chooseSense,&ChooseSense::chooseSenseBack,this,[=](){
        this->show();
        chooseSense->hide();
    });
    connect(btn_start,&QPushButton::clicked,btn_start,[=](){
        btn_start->dumpAnimation();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            chooseSense->show();
        });
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制左上角图标
    QPixmap backgroundIcon(":/res/Title.png"); // 替换为您的背景图片路径
    painter.drawPixmap(10,30, backgroundIcon.scaled(backgroundIcon.width()*0.5,backgroundIcon.height()*0.5));
}

