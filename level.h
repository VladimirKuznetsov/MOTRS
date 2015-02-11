#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QTimer>
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
    QTimer *updateTimer;
    unsigned short numberOfEnemies;

    //���������� �������������� ��������� �����
    short PLAYER_HEIGHT;
    short PLAYER_WIDTH;
    short ENEMY_HEIGHT;
    short ENEMY_WIDTH;
    
signals:
    void levelCompleted (bool result, Level * level);
    
public slots:
    
};

#endif // LEVEL_H
