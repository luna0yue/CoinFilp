#include "playsence.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlaySence::PlaySence(int levelNum){
    this->levelIndex = levelNum;
    this->isWin = false;

    //初始化游戏场景
    //页面设置
    this->setFixedSize(600, 1000);
    this->setWindowIcon(QIcon(":/res/Cion0001.png"));
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //游戏音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav");
    QSound * conFlipSound = new QSound(":/res/ConFlipSound.wav");
    QSound * levelWinSound = new QSound(":/res/LevelWinSound.wav");

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()- backBtn->width() - 10, this->height() - backBtn->height() -10);

    connect(backBtn, &MyPushButton::clicked, [=](){
        backSound->play();
        emit this->chooseSenceBack();
    });

    //底部显示关卡
    QLabel * label = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(10);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str);
    label->setGeometry(QRect(30, this->height() - 50, 120, 50));

    //赢的图片
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    pix = pix.scaled(pix.width() * 2, pix.height() * 2);

    QLabel * WinLabel = new QLabel;
    WinLabel->setGeometry(0, 0, pix.width(), pix.height());
    WinLabel->setPixmap(pix);
    WinLabel->setParent(this);
    WinLabel->move((this->width() - pix.width())*0.5, - pix.height());


    //初始化每个关卡的二维数组
    dataconfig config;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //显示金币背景图案
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            QLabel * label = new QLabel;
            label->setGeometry(0, 0, 100, 100);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(130 + i * 100, 300 + j * 100);

            QString str = ":/res/Coin0008.png";
            if(this->gameArray[i][j]){
                str = ":/res/Coin0001.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(132 + i * 100, 329 + j * 100);

            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];
            coin->isWin = false;

            coinBtn[i][j] = coin;

            connect(coin, &MyCoin::clicked, [=](){
                conFlipSound->play();

                coin->changeFlag();
                this->gameArray[i][j] = (this->gameArray[i][j] == 0? 1:0);

                //反转周围金币
                if(i + 1 <= 3){
                    coinBtn[i + 1][j]->changeFlag();
                    this->gameArray[i + 1][j] = this->gameArray[i + 1][j] == 0? 1:0;
                }
                if(i - 1 >= 0){
                    coinBtn[i - 1][j]->changeFlag();
                    this->gameArray[i - 1][j] = this->gameArray[i - 1][j] == 0? 1:0;
                }

                if(j + 1 <= 3){
                    coinBtn[i][j + 1]->changeFlag();
                    this->gameArray[i][j + 1] = this->gameArray[i][j + 1] == 0? 1:0;
                }

                if(j - 1 >= 0){
                    coinBtn[i][j - 1]->changeFlag();
                    this->gameArray[i][j - 1] = this->gameArray[i][j - 1] == 0? 1:0;
                }

                //判断是否胜利
                this->isWin = true;
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        if(this->gameArray[i][j] == 0){
                            this->isWin = false;
                            break;
                        }
                    }
                 }
                if(this->isWin){
                    for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                           this->coinBtn[i][j]->isWin = true;
                            }
                        }
                    levelWinSound->play();
                    this->showWinPicture(WinLabel);

                }

            });


        }
    }
}

void PlaySence::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 1.5, pix.height() * 1.5);
    painter.drawPixmap((this->width() - pix.width())*0.5, 40, pix);

}

void PlaySence::showWinPicture(QLabel * label){

    QPropertyAnimation * animation = new QPropertyAnimation(label, "geometry");
    animation->setDuration(800);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->setStartValue(QRect((this->width() - label->width())*0.5, - label->height(), label->width(), label->height()));
    animation->setEndValue(QRect((this->width() - label->width())*0.5, label->height() - 50, label->width(), label->height()));
    animation->start();

}
