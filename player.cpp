#include "player.h"
#include "floor.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

//конструктор класса
Player::Player(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    verticalSpeed = 0;
    horizontalSpeed = 5;
    jumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//обработака нажатия клавиши
void Player::keyPressEvent(QKeyEvent *event)
{
    //прыжок по нажатию на пробел
    if ((event->key() == Qt::Key_Space) & (jumps < 2)) {
        jumps++;
        verticalSpeed = (16/jumps);
    }

}

//движение игрока
void Player::move()
{
    setPos(x() + horizontalSpeed, y() - verticalSpeed);
    verticalSpeed -= 1;

    //ограничение по вертикальному перемещению
    solveCollisions();
}

//разрешение коллизий с другими объектами
void Player::solveCollisions()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Floor)) {
            //упёрлись головой в потолок
            if (verticalSpeed > 0) {
                qDebug() << "Ceiling";
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
                jumps = 2;
            }
            //провалились сквозь землю
            if (verticalSpeed < 0) {
                qDebug() << "Floor";bool collision = true;
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
                jumps = 0;
            }
            verticalSpeed = 0;
            break;
        }
    }
}
