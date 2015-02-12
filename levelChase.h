#ifndef LEVELCHASE_H
#define LEVELCHASE_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "level.h"

class LevelChase : public Level
{
    Q_OBJECT
public:
    LevelChase(QGraphicsView * parent);
    void followEnemy();

signals:
public slots:
    void checkRules();
};

#endif // LEVELCHASE_H
