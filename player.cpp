#include "player.h"
#include "floor.h"
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

    horizontalSpeed = HORIZONTAL_SPEED;
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

//движение игрока
void Player::move()
{
    setPos(x() + horizontalSpeed, y());

    //ограничение по вертикальному перемещению
    solveHorizontalCollisions();

    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= GRAVITY;

    //ограничение по вертикальному перемещению
    solveVerticalCollisions();

    //следим за передвижениями игрока
    game->followPlayer();
}

//разрешение коллизий с другими объектами при вертикальном движении
void Player::solveVerticalCollisions()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Floor)) {
            //упёрлись головой в потолок
            if (verticalSpeed > 0) {
                bool collision = true;
                while (collision) {
                    setPos(x(), y() + 1);
                    QList <QGraphicsItem *> newCollisionList = collidingItems();
                    collision = false;
                    for (int i = 0; i < newCollisionList.size(); i++) {
                        if (typeid(*newCollisionList[i]) == typeid(Floor)) {
                            collision = true;
                        }
                    }
                }
                numberOfJumps = 2;
            }
            //провалились сквозь землю
            if (verticalSpeed < 0) {
                bool collision = true;
                while (collision) {
                    setPos(x(), y() - 1);
                    QList <QGraphicsItem *> newCollisionList = collidingItems();
                    collision = false;
                    for (int i = 0; i < newCollisionList.size(); i++) {
                        if (typeid(*newCollisionList[i]) == typeid(Floor)) {
                            collision = true;
                        }
                    }
                }
                numberOfJumps = 0;
            }
            verticalSpeed = 0;
            break;
        }
    }
}

//разрешение коллизий с другими объектами при горизонтальном движении
void Player::solveHorizontalCollisions()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Floor)) {
            //упёрлись вправо
            if (horizontalSpeed >= 0) {
                bool collision = true;
                while (collision) {
                    setPos(x() - 1, y());
                    QList <QGraphicsItem *> newCollisionList = collidingItems();
                    collision = false;
                    for (int i = 0; i < newCollisionList.size(); i++) {
                        if (typeid(*newCollisionList[i]) == typeid(Floor)) {
                            collision = true;
                        }
                    }
                };
            }
            //провалились сквозь землю
            if (horizontalSpeed < 0) {
                bool collision = true;
                while (collision) {
                    setPos(x() + 1, y());
                    QList <QGraphicsItem *> newCollisionList = collidingItems();
                    collision = false;
                    for (int i = 0; i < newCollisionList.size(); i++) {
                        if (typeid(*newCollisionList[i]) == typeid(Floor)) {
                            collision = true;
                        }
                    }
                }
            }
            break;
        }
    }
}
