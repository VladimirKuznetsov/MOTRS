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
    void init(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
public slots:
    void checkRules();
    void followEnemy();
};

#endif // LEVELCHASE_H
