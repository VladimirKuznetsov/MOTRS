#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include "player.h"
#include "enemy.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void init(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void followEnemy();
    QGraphicsScene * scene;
    Player * player;
    Enemy * enemy;

    //геометрические параметры
    short CELL_SIZE;
    short WINDOW_WIDTH;
    short WINDOW_HEIGHT;
    short PLAYER_WIDTH;
    short PLAYER_HEIGHT;
    short ENEMY_WIDTH;
    short ENEMY_HEIGHT;
signals:
public slots:
    void checkRules();
};

#endif // GAME_H
