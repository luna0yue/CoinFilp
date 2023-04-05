#include "chooselevelsence.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QSound>


ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //页面设置
    this->setFixedSize(600, 1000);
    this->setWindowIcon(QIcon(":/res/Cion0001.png"));
    this->setWindowTitle("关卡选择");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");

    QSound * clinkSound = new QSound(":/res/TapButtonSound.wav");
    QSound * backSound = new QSound(":/res/BackButtonSound.wav");

    //返回按钮
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() - 10, this->height() - backBtn->height() - 10);

    connect(backBtn, &MyPushButton::clicked, [=](){
        backSound->play();
        emit this->chooseSenceBack();

    });

    //选择关卡按钮
    for(int i = 0; i < 20; i++){
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i % 4 * 100 + 130, i / 4 * 100 + 280 );


        connect(menuBtn, &MyPushButton::clicked, [=](){
            clinkSound->play();
            play = new PlaySence(i + 1);
            this->hide();
            play->setGeometry(this->geometry());
            play->show();

            connect(play, &PlaySence::chooseSenceBack, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = nullptr;
            });
        });

        QLabel * label = new QLabel(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(i % 4 * 100 + 130, i / 4 * 100 + 280);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}


void ChooseLevelSence::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 1.5, pix.height() * 1.5);
    painter.drawPixmap((this->width() - pix.width())*0.5, 40, pix);

}
