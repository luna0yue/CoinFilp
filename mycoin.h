#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数代表金币还是银币的路径
    MyCoin(QString btnImg);
    void changeFlag();
    QTimer * timer;
    int curr_page = 1;
    bool isAnimation = false;

    void mousePressEvent(QMouseEvent *);

    int posX;
    int posY;
    bool flag;
    bool isWin;

signals:

public slots:
};

#endif // MYCOIN_H
