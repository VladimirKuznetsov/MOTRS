#include "levelChase.h"
#include "cell.h"
#include "game.h"
//#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>
#include <QGraphicsItem>
#include <float.h>

extern Game * game;

//конструктор
LevelChase::LevelChase(QGraphicsView * parent) : Level(parent)
{
}

//следим за перемещениями игрока
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy[0], game->WINDOW_WIDTH * 1/5, 0);
}

//проверка условий победы и поражения
void LevelChase::checkRules()
{
    //камера следит за противником
    followEnemy();

    if (check == true)
    {
        //победа если персонаж догнал соперника
        QList <QGraphicsItem *> collisionList = player->collidingItems();
        if (player->x() > enemy[0]->x() + enemy[0]->boundingRect().width())
        {
            emit win();
            return;
        }

        //поражение, если персонаж сильно отстал
        if (enemy[0]->x() - player->x() > game->CELL_SIZE * 20) {
            check = false;
            gameOver("Похитителю удалось скрыться.");
            return;
        }

        //поражение, если противник уехал за границу экрана
        if (enemy[0]->x() > sceneRect().width()) {
            check = false;
            gameOver("Похитителю удалось скрыться.");
            return;
        }
    }
}
