#include "player.h"
#include "floor.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

//����������� ������
Player::Player(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    verticalSpeed = 0;
    horizontalSpeed = 5;
    jumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//���������� ������� �������
void Player::keyPressEvent(QKeyEvent *event)
{
    //������ �� ������� �� ������
    if ((event->key() == Qt::Key_Space) & (jumps < 2)) {
        jumps++;
        verticalSpeed = (16/jumps);
    }

}

//�������� ������
void Player::move()
{
    setPos(x() + horizontalSpeed, y() - verticalSpeed);
    verticalSpeed -= 1;

    //����������� �� ������������� �����������
    solveCollisions();
}

//���������� �������� � ������� ���������
void Player::solveCollisions()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Floor)) {
            //������� ������� � �������
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
            //����������� ������ �����
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
