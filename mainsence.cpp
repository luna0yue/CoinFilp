#include "mainsence.h"
#include "ui_mainsence.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainSence::MainSence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSence)
{
    ui->setupUi(this);

    //主界面设置
    setFixedSize(600, 1000);
    setWindowIcon(QIcon(":/res/Cion0001.png"));
    setWindowTitle("阿月带你翻金币");

    //设置音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav");

    //退出动作实现
    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width()- startBtn->width())*0.5, this->height() * 0.8);

    //选择关卡
    chooseLevelSence = new ChooseLevelSence;

    //监听选择关卡场景
    connect(chooseLevelSence, &ChooseLevelSence::chooseSenceBack, this, [=](){
        QTimer::singleShot(100, this, [=](){
            this->setGeometry(chooseLevelSence->geometry());
            chooseLevelSence->hide();
            this->show();
        });

    } );

    connect(startBtn, &MyPushButton::clicked, [=](){
        startSound->play();
        startBtn->zoom(false);
        startBtn->zoom(true);
        QTimer::singleShot(500, this, [=](){
            this->hide();
            chooseLevelSence->setGeometry(this->geometry());
            chooseLevelSence->show();
        });
    });

}

 void MainSence::paintEvent(QPaintEvent *){
     QPainter painter(this);
     QPixmap pix;

     pix.load(":/res/PlayLevelSceneBg.png");
     painter.drawPixmap(0, 0, this->width(), this->height(), pix);

     pix.load(":/res/Title.png");
     //pix = pix.scaled(pix.width(), pix.height() * 1.5);
     painter.drawPixmap(30, 40, pix);

}


MainSence::~MainSence()
{
    delete ui;
}
