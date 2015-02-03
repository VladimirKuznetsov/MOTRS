#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include "player.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    void init();
    void loadScene(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void followPlayer();
    QGraphicsScene * scene;
    Player * player;

    //геометрические параметры сцены
    short WINDOW_WIDTH;
    short WINDOW_HEIGHT;
    short PLAYER_WIDTH;
    short PLAYER_HEIGHT;
    short CELL_SIZE;
signals:
public slots:
};

#endif // GAME_H
