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

//следим за перемещениями противника
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy[0], game->WINDOW_WIDTH * 1/5, 0);

    //имитируем нажатие клавиши "бег"
    if (dialog->isOn == false)
    {
        QKeyEvent * keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Right, 0, "", false, 1);
        player->keyPressEvent(keyEvent);
        keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Shift, 0, "", false, 1);
        player->keyPressEvent(keyEvent);
    }
}

//прыжок по нажатию на экран
void LevelChase::mousePressEvent(QMouseEvent *event)
{
    if (dialog->isOn == true)
    {
        dialog->nextLine();
    } else
    {
        QKeyEvent * keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Up, 0, "", false, 1);
        player->keyPressEvent(keyEvent);
    }
}

//блокируем обработку двойного клика
void LevelChase::mouseDoubleClickEvent(QMouseEvent *event)
{

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
