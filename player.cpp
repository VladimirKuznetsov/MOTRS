#include "player.h"
#include "solid.h"
#include "game.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

extern Game * game;

//конструктор класса
Player::Player(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    JUMP_SPEED = (short)(game->CELL_SIZE / 4);
    HORIZONTAL_SPEED = (short)(game->CELL_SIZE / 10);
    GRAVITY = (short)(game->CELL_SIZE / 60);

    horizontalSpeed = 0;
    verticalSpeed = 0;
    numberOfJumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//совершить прыжок
void Player::jump()
{
    if (numberOfJumps < 2) {
        numberOfJumps++;
        verticalSpeed = (JUMP_SPEED / numberOfJumps);
    }
}

//увеличить скорость вправо
void Player::right()
{
    horizontalSpeed += HORIZONTAL_SPEED;
}

//увеличить скорость влево
void Player::left()
{
    horizontalSpeed -= HORIZONTAL_SPEED;
}

//движение игрока
void Player::move()
{
    //перемещаемся по горизонтали
    setPos(x() + horizontalSpeed, y());

    //ограничение по горизонтальному перемещению
    if (collideWithSolid() == true)
    {
        //упёрлись вправо
        if (horizontalSpeed >= 0) {
            do {
                setPos(x() - 1, y());
            } while (collideWithSolid() == true);
        }
        //упёрлись влево
        if (horizontalSpeed < 0) {
            do {
                setPos(x() + 1, y());
            } while (collideWithSolid() == true);
        }
    }

    //перемещаемся по вертикали
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= GRAVITY;

    //ограничение по вертикальному перемещению
    if (collideWithSolid() == true)
    {
        //упёрлись головой в потолок
        if (verticalSpeed > 0) {
            do {
                setPos(x(), y() + 1);
            } while (collideWithSolid() == true);
            numberOfJumps = 2;
        }
        //провалились сквозь землю
        if (verticalSpeed <= 0) {
            do {
                setPos(x(), y() - 1);
            } while (collideWithSolid() == true);
            numberOfJumps = 0;
        }
        verticalSpeed = 0;
    }

    //следим за передвижениями игрока
    game->followPlayer();
}

//проверка на коллизии с твёрдыми предметами
bool Player::collideWithSolid()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Solid)) {
            return true;
        }
    }
    return false;
}
