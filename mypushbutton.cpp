#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

 MyPushButton::MyPushButton(QString noramlImg, QString pressImg){
     this->normalImgPath = noramlImg;
     this->pressImgPath = pressImg;

     QPixmap pix;
     bool ret = pix.load(noramlImg);
     if(!ret){
         qDebug() << "图片加载失败！";
     }

     //固定大小
     this->setFixedSize(pix.width(), pix.height());
     //设置不规则图片样式
     this->setStyleSheet("QPushButton{border:0px;}");
     //设置图标
     this->setIcon(pix);
     //设置图标大小
     this->setIconSize(QSize(pix.width(), pix.height()));

 }


 void MyPushButton::zoom(bool up){
     //设置动画

     QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
     animation->setDuration(100);

     if(up){
        animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
        animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
     }else{
        animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
        animation->setEndValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));
     }
     animation->start();
}

 void MyPushButton::mousePressEvent(QMouseEvent *e){

     if(this->pressImgPath != ""){
         QPixmap pix;
         bool ret = pix.load(this->pressImgPath);
         if(!ret){
             qDebug() << "图片加载失败！";
         }


         this->setFixedSize(pix.width(), pix.height());
         this->setStyleSheet("QPushButton{border:0px;}");
         this->setIcon(pix);
         this->setIconSize(QSize(pix.width(), pix.height()));

     }

     return QPushButton::mousePressEvent(e);

 }

 void MyPushButton::mouseReleaseEvent(QMouseEvent *e){

     if(this->pressImgPath != ""){
         QPixmap pix;
         bool ret = pix.load(this->normalImgPath);
         if(!ret){
             qDebug() << "图片加载失败！";
         }
         this->setFixedSize(pix.width(), pix.height());
         this->setStyleSheet("QPushButton{border:0px;}");
         this->setIcon(pix);
         this->setIconSize(QSize(pix.width(), pix.height()));

     }
     return QPushButton::mouseReleaseEvent(e);
 }


