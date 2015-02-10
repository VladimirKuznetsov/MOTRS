#include "game.h"
#include <math.h>
#include <QDebug>
#include "levelChase.h"

Game::Game()
{
    WINDOW_HEIGHT = 700;
    WINDOW_WIDTH = 1100;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //����������� ��������� ����������� ����
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
        "fffgffffffffffgffyfffyfffgfffffffyfffffffgfffffffffygfffffgfffffffyfgfffyfffffff",
    };

    QString testMap[] = {
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "           ",
        "  p        ",
        "      hhh e",
        "fffffffffff",
    };

    LevelChase * levelChase = new LevelChase(this);
    levelChase->init(levelMap);

    //����� �� �����
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
