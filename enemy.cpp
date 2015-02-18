#include "enemy.h"
#include "cell.h"
#include <typeinfo>
#include <math.h>
#include <float.h>
//#include <QDebug>
#include "game.h"

extern Game * game;

Enemy::Enemy(QPixmap _spriteSheet, QObject *parent) : QObject(parent)
{
    frame = 0;
    animationSpeed = 0.2;
    spriteSheet = _spriteSheet;
    setPixmap(spriteSheet.copy(0 * (int)frame, 0, 194, 120));
    HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) * 17 / 100);
    numberOfJumps = 2;
    horizontalSpeed = 0;
    verticalSpeed = 0;
}

void Enemy::move()
{
    //перемещаемся по горизонтали
    int oldX = x();
    setPos(x() + horizontalSpeed, y());

    //ограничение по горизонтальному перемещению
    if (collideWithFloor() == true)
    {
        setPos(oldX, y());
    }

    //плавный разгон
    static int i = 0;
    i++;
    if (i > 8) {
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
    int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    //ограничение по вертикальному перемещению
    if (collideWithFloor() == true)
    {
        //упёрлись головой в потолок
        if (verticalSpeed > 0) {
            numberOfJumps = 2;
        }
        //провалились сквозь землю
        if (verticalSpeed <= 0) {
            numberOfJumps = 0;
        }
        setPos(x(), oldY);
        verticalSpeed = 0;
    }

    //анимация движения
    frame += animationSpeed;
    if (frame >= 2) frame = 0;
    setPixmap(spriteSheet.copy(194 * (int)frame, 0, 194, 120));
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

