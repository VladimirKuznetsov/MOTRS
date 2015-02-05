#include "game.h"
#include <math.h>
#include <QDebug>
#include "levelChase.h"

Game::Game()
{
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1000;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //настраиваем параметры отображения окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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
        "  p                                                                            ",
        "      hhh e    h   h   hh     h                      h         h h             ",
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
    };


    LevelChase * levelChase = new LevelChase(this);
    levelChase->init(levelMap);

    //вывод на экран
    show();
}

void Game::levelCompleted(bool result, Level * level)
{
    if (result == true) {
        qDebug() << "WE GOT A WINNER";
    } else {
        qDebug() << "LOOK AT THIS LOOSER";
        delete level;
        loadLevel(0);
    }
}
