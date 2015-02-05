#ifndef LEVELCHASE_H
#define LEVELCHASE_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "level.h"
#include "player.h"
#include "enemy.h"

class LevelChase : public Level
{
    Q_OBJECT
public:
    LevelChase(QGraphicsView * parent);
    void init(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    Player * player;
    Enemy * enemy;

signals:
public slots:
    void checkRules();
    void followEnemy();
};

#endif // LEVELCHASE_H
