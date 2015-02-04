#include "enemy.h"
#include "game.h"
#include "cell.h"
#include <QTimer>
#include <typeinfo>
#include <math.h>
#include <float.h>

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    GRAVITY = ceil(float(game->CELL_SIZE) / 60);

    HORIZONTAL_SPEED = ceil(float(game->player->HORIZONTAL_SPEED) * 9 / 10);
    horizontalSpeed = 0;
    verticalSpeed = 0;
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
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
    verticalSpeed -= GRAVITY;

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

    //следим за движением
    game->followEnemy();
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

