#include "enemy.h"
#include "cell.h"
#include <typeinfo>
#include <math.h>
#include <float.h>
#include "game.h"
#include <QDebug>

extern Game * game;

Enemy::Enemy(QPixmap _spriteSheet, QObject *parent) : QObject(parent)
{
    frame = 0;
    animationSpeed = 8;
    spriteSheet = _spriteSheet;
    setPixmap(spriteSheet.copy(0 * (int)frame, 0, 194, 120));
    HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) * 18 / 100) * 40;
    numberOfJumps = 2;
    horizontalSpeed = 0;
    verticalSpeed = 0;

    time = new QTime();
    time->start();
}

void Enemy::move()
{
    float deltaTime = (float) time->elapsed() / 1000;
    if (deltaTime > 0.1) deltaTime = 0.1;
    time->restart();

    //перемещаемся по горизонтали
    setPos(x() + horizontalSpeed * deltaTime, y());

    //плавный разгон
    static int i = 0;
    i += deltaTime * 1000;
    if (i > 1) {
        if (HORIZONTAL_SPEED > 0) {
            if (horizontalSpeed < HORIZONTAL_SPEED) horizontalSpeed += 5;
            if (horizontalSpeed > HORIZONTAL_SPEED) horizontalSpeed -= 5;
        } else if (HORIZONTAL_SPEED < 0) {
            if (horizontalSpeed > HORIZONTAL_SPEED) horizontalSpeed += 5;
            if (horizontalSpeed < HORIZONTAL_SPEED) horizontalSpeed -= 5;
        }if (VERTICAL_SPEED > 0) {
            if (verticalSpeed < VERTICAL_SPEED) verticalSpeed += 5;
            if (verticalSpeed > VERTICAL_SPEED) verticalSpeed -= 5;
        } else if (VERTICAL_SPEED < 0) {
            if (verticalSpeed > VERTICAL_SPEED) verticalSpeed += 5;
            if (verticalSpeed < VERTICAL_SPEED) verticalSpeed += 5;
        }
        i = 0;
    }

    //перемещаемся по вертикали
    int oldY = y();
    setPos(x(), y() - verticalSpeed * deltaTime);
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
    frame += animationSpeed * deltaTime;
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

