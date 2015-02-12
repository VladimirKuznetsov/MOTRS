#include "game.h"
#include <math.h>
#include <QDebug>
#include <QVector>
#include <QTextCodec>
#include "levelChase.h"

QString testMap[] = {
    "LEVEL: CHASE"
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
    "      hhh v",
    "fffffffffff",
};

QString levelMap0[] =
{
    "LEVEL: CHASE",
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
    "  p   hhh v    h   h   hh     h                      h         h h             ",
    "fffyffffffffffgffffffyfffffffffffyfffffffgffffffffygfffffgfffffffffffffyfffffff",
};

Game::Game()
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

    levelNumber = 0;
    WINDOW_HEIGHT = 700;
    WINDOW_WIDTH = 1100;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //настраиваем параметры отображения окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::loadLevel()
{
    switch (levelNumber)
    {
    case 0:
        if (levelMap0[0] == QString("LEVEL: CHASE"))
        {
            LevelChase * levelChase = new LevelChase(this);
            levelChase->init(levelMap0);
        }
        break;
    }

    //вывод на экран
    show();
}

void Game::levelCompleted(bool result, Level * level)
{
    if (result == true) {
        qDebug() << "WE GOT A WINNER";
        levelNumber++;
    } else {
        qDebug() << "LOOK AT THIS LOOSER";
        delete level;
        loadLevel();
    }
}
