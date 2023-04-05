#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include "playsence.h"

class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlaySence * play = NULL;

signals:
    chooseSenceBack();

public slots:
};

#endif // CHOOSELEVELSENCE_H
