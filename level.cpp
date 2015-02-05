#include "level.h"
#include "game.h"

extern Game * game;

Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{
    //определ€ем геометрические параметры сцены
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    connect(this, SIGNAL(levelCompleted(bool)), game, SLOT(levelCompleted(bool)));
}

void Level::gameOver(QString comment)
{
    emit levelCompleted(false);
}
