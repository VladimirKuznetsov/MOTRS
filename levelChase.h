#ifndef LEVELCHASE_H
#define LEVELCHASE_H

#include <QObject>
#include <QGraphicsView>
#include <QString>
#include "level.h"
#include "player.h"
#include "enemy.h"

class LevelChase : public Level
{
    Q_OBJECT
public:
    LevelChase();
    void init(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QGraphicsScene * scene;
    Player * player;
    Enemy * enemy;

    //геометрические параметры
    short PLAYER_WIDTH;
    short PLAYER_HEIGHT;
    short ENEMY_WIDTH;
    short ENEMY_HEIGHT;
signals:
public slots:
    void checkRules();
    void followEnemy();
};

#endif // LEVELCHASE_H
