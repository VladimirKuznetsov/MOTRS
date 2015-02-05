#include "enemy.h"
#include "cell.h"
#include <typeinfo>
#include <math.h>
#include <float.h>
#include "game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{

    HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) * 9 / 100);
    //HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) * 5 / 100);
    horizontalSpeed = 0;
    verticalSpeed = 0;
}

void Enemy::move()
{
    //перемещаемся по горизонтали
    setPos(x() + horizontalSpeed, y());

    //ограничение по горизонтальному перемещению
    if (collideWithFloor() == true)
    {
        //упёрлись вправо
        if (horizontalSpeed >= 0) {
            do {
                setPos(x() - 1, y());
            } while (collideWithFloor() == true);
        }
        //упёрлись влево
        if (horizontalSpeed < 0) {
            do {
                setPos(x() + 1, y());
            } while (collideWithFloor() == true);
        }
    }

    //плавный разгон
    static int i = 0;
    i++;
    if (i > 20) {
        if (HORIZONTAL_SPEED > 0) {
            if (horizontalSpeed < HORIZONTAL_SPEED) horizontalSpeed++;
            if (horizontalSpeed > HORIZONTAL_SPEED) horizontalSpeed--;
        } else if (HORIZONTAL_SPEED < 0) {
            if (horizontalSpeed > HORIZONTAL_SPEED) horizontalSpeed++;
            if (horizontalSpeed < HORIZONTAL_SPEED) horizontalSpeed--;
        }if (VERTICAL_SPEED > 0) {
            if (verticalSpeed < VERTICAL_SPEED) verticalSpeed++;
            if (verticalSpeed > VERTICAL_SPEED) verticalSpeed--;
        } else if (VERTICAL_SPEED < 0) {
            if (verticalSpeed > VERTICAL_SPEED) verticalSpeed++;
            if (verticalSpeed < VERTICAL_SPEED) verticalSpeed--;
        }
        i = 0;
    }

    //перемещаемся по вертикали
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    //ограничение по вертикальному перемещению
    if (collideWithFloor() == true)
    {
        //упёрлись головой в потолок
        if (verticalSpeed > 0) {
            do {
                setPos(x(), y() + 1);
            } while (collideWithFloor() == true);
        }
        //провалились сквозь землю
        if (verticalSpeed <= 0) {
            do {
                setPos(x(), y() - 1);
            } while (collideWithFloor() == true);
        }
        verticalSpeed = 0;
    }
}

//проверка на коллизии с твёрдыми предметами
bool Enemy::collideWithFloor()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Cell)) {
            if (((Cell *)(collisionList[i]))->isFloor == true) {
                return true;
            }
        }
    }
    return false;
}

