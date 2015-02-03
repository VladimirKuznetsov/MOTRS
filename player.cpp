#include "player.h"
#include "solid.h"
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

//��������� ������
void Player::jump()
{
    if (numberOfJumps < 2) {
        numberOfJumps++;
        verticalSpeed = (JUMP_SPEED / numberOfJumps);
    }
}

//��������� �������� ������
void Player::right()
{
    horizontalSpeed += HORIZONTAL_SPEED;
}

//��������� �������� �����
void Player::left()
{
    horizontalSpeed -= HORIZONTAL_SPEED;
}

//�������� ������
void Player::move()
{
    //������������ �� �����������
    setPos(x() + horizontalSpeed, y());

    //����������� �� ��������������� �����������
    if (collideWithSolid() == true)
    {
        //������� ������
        if (horizontalSpeed >= 0) {
            do {
                setPos(x() - 1, y());
            } while (collideWithSolid() == true);
        }
        //������� �����
        if (horizontalSpeed < 0) {
            do {
                setPos(x() + 1, y());
            } while (collideWithSolid() == true);
        }
    }

    //������������ �� ���������
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= GRAVITY;

    //����������� �� ������������� �����������
    if (collideWithSolid() == true)
    {
        //������� ������� � �������
        if (verticalSpeed > 0) {
            do {
                setPos(x(), y() + 1);
            } while (collideWithSolid() == true);
            numberOfJumps = 2;
        }
        //����������� ������ �����
        if (verticalSpeed <= 0) {
            do {
                setPos(x(), y() - 1);
            } while (collideWithSolid() == true);
            numberOfJumps = 0;
        }
        verticalSpeed = 0;
    }

    //������ �� �������������� ������
    game->followPlayer();
}

//�������� �� �������� � ������� ����������
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
