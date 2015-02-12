#include "levelInvestigate.h"
#include "game.h"
#include <QDebug>

extern Game * game;

//конструктор
LevelInvestigate::LevelInvestigate(QGraphicsView *parent) : Level(parent)
{
}

//проверка условий победы и поражения
void LevelInvestigate::checkRules()
{
    //камера следит за противником
    followPlayer();

    //сверяем списки улик
    bool unfoundClues = false;
    for (int i = 0; i < clues.size(); i++)
    {
        if (player->clues.contains(clues[i]) == false) unfoundClues = true;
    }

    //если все улики найдены, уровень закончен
    if (unfoundClues == false)
    {
        levelCompleted(endMessage);
    }
}

//камера следит за передвижениями игрока
void LevelInvestigate::followPlayer()
{
    game->ensureVisible(player, game->WINDOW_WIDTH * 1/5, 0);
}
