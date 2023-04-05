#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "chooselevelsence.h"

namespace Ui {
class MainSence;
}

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSence(QWidget *parent = 0);
    ~MainSence();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    ChooseLevelSence * chooseLevelSence = nullptr;

private:
    Ui::MainSence *ui;
};

#endif // MAINSENCE_H
