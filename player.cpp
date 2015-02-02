#include "player.h"
#include "floor.h"
#include "game.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

extern Game * game;

//����������� ������
Player::Player(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    verticalSpeed = 0;
    horizontalSpeed = 5;
    numberOfJumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//��������� ������
void Player::jump()
{
    if (numberOfJumps < 2) {
        numberOfJumps++;
        verticalSpeed = (16/numberOfJumps);
    }
}

//�������� ������
void Player::move()
{
    //����������� ������
    setPos(x() + horizontalSpeed, y() - verticalSpeed);
    verticalSpeed -= 1;

    //����������� �� ������������� �����������
    solveCollisions();

    //������ �� �������������� ������
    game->followPlayer();
}

//���������� �������� � ������� ���������
void Player::solveCollisions()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Floor)) {
            //������� ������� � �������
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
            //����������� ������ �����
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
