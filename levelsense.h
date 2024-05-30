#ifndef LEVELSENSE_H
#define LEVELSENSE_H

#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QLabel>
#include <QMessageBox>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

namespace Ui {
class LevelSense;
}

class LevelSense : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSense(QWidget *parent = nullptr);
    LevelSense(int level,QWidget *parent = nullptr);
    ~LevelSense();

protected:
    void paintEvent(QPaintEvent *event)override;

signals:
    void back();

private:
    Ui::LevelSense *ui;
    int level;
    int levelMsg[4][4];
    MyCoin *coins[4][4];
    bool isWin;
};

#endif // LEVELSENSE_H
