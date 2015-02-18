#include "levelInvestigate.h"
#include "game.h"
#include <typeinfo>
#include <QList>
//#include <QDebug>

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

    //если игрок стоит на клетке выхода
    QList <QGraphicsItem *> availableItems = player->actionArea->collidingItems();
    for (int i = 0; i < availableItems.size(); i++)
    {
        //обнаруживаем клетку выхода
        if ((typeid(*availableItems[i]) == typeid(Cell)) && (((Cell*)availableItems[i])->isTarget == true))
        {
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
    }
}

//камера следит за передвижениями игрока
void LevelInvestigate::followPlayer()
{
    game->ensureVisible(player, game->WINDOW_WIDTH * 1/5, 0);
}
