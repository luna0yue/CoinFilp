#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片 % 1 加载失败").arg(btnImg);
        qDebug() << str;
        return;
    }

    //pix = pix.scaled(80, 80);
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=](){
       QPixmap pix;
       QString str;
       if(this->flag){
            str = QString(":/res/Coin000%1.png").arg(this->curr_page);
       }else{
            str = QString(":/res/Coin000%1.png").arg(9 - this->curr_page);
       }
       pix.load(str);

       this->setFixedSize(QSize(pix.width(), pix.height()));
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(), pix.height()));

       curr_page++;
       if(this->curr_page == 9){
           this->curr_page = 1;
           timer->stop();
           this->flag = !this->flag;
           this->isAnimation = false;
       }

    });
}

void MyCoin::changeFlag(){

      timer->start(50);
      this->isAnimation = true;

}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation || this->isWin){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}

