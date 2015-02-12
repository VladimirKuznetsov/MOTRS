#include "levelInvestigate.h"
#include "game.h"
#include <QDebug>

extern Game * game;

//конструктор
LevelInvestigate::LevelInvestigate(QGraphicsView *parent) : Level(parent)
{
}

//проверка условий победы и поражени€
void LevelInvestigate::checkRules()
{
    //камера следит за противником
    followPlayer();

    //свер€ем списки улик
    bool unfoundClues = false;
    for (int i = 0; i < clues.size(); i++)
    {
        if (player->clues.contains(clues[i]) == false) unfoundClues = true;
    }

    //если все улики найдены, уровень закончен
    if (unfoundClues == false)
    {
        QString exitingMessage[10] =
        {
            "»так, наша лучша€ зацепка это пропавший сторож...",
            "Ќо где его искать?",
            "...",
            " ак? ”же шесть вечера?!",
            "—торожем займусь завтра на свежую голову, а сейчас домой.",
        };
        levelCompleted(exitingMessage);
    }
}

//камера следит за передвижени€ми игрока
void LevelInvestigate::followPlayer()
{
    game->ensureVisible(player, game->WINDOW_WIDTH * 1/5, 0);
}
