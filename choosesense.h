#ifndef CHOOSESENSE_H
#define CHOOSESENSE_H

#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QLabel>
#include "mypushbutton.h"
#include "levelsense.h"

namespace Ui {
class ChooseSense;
}

class ChooseSense : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseSense(QWidget *parent = nullptr);
    ~ChooseSense();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void chooseSenseBack();
    void level(int level);
private:
    Ui::ChooseSense *ui;
};

#endif // CHOOSESENSE_H
