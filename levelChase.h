#ifndef LEVELCHASE_H
#define LEVELCHASE_H

#include <QObject>
#include "level.h"

class LevelChase : public Level
{
    Q_OBJECT
public:
    LevelChase(QGraphicsView * parent);
    void followEnemy();
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

signals:
public slots:
    void checkRules();
};

#endif // LEVELCHASE_H
