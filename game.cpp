#include "game.h"
#include <math.h>
#include "levelChase.h"

Game::Game()
{
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1000;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);
}

void Game::loadLevel(int levelNumber)
{
    QString levelMap[] = {
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "  p   hhh e    h   h   hh     h                      h         h h             ",
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
    };

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //настраиваем параметры отображения
    LevelChase * levelChase = new LevelChase();
    levelChase->init(levelMap);

    //вывод на экран
    show();
}
