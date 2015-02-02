#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "player.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void followPlayer();
    QGraphicsScene * scene;
    Player * player;
signals:
public slots:
};

#endif // GAME_H
