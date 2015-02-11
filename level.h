#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include "player.h"
#include "enemy.h"

class Level : public QGraphicsScene
{
    Q_OBJECT
public:
    Level(QGraphicsView * parent);
    void init (QString levelMap[]);
    void gameOver (QString comment);
    Player * player;
    Enemy * enemy[10];
    unsigned short numberOfEnemies;

    //определ€ем геометрические параметры сцены
    short PLAYER_HEIGHT;
    short PLAYER_WIDTH;
    short ENEMY_HEIGHT;
    short ENEMY_WIDTH;
    
signals:
    void levelCompleted (bool result, Level * level);
    
public slots:
    
};

#endif // LEVEL_H
