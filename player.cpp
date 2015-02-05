#include "player.h"
#include "cell.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include <math.h>
#include <float.h>
#include <game.h>

extern Game * game;

//����������� ������
Player::Player(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) / 10);

    horizontalSpeed = 0;
    verticalSpeed = 0;
    numberOfJumps = 2;
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
    int oldX = x();
    setPos(x() + horizontalSpeed, y());

    //����������� �� ��������������� �����������
    if (collideWithSolid() == true)
    {
        setPos(oldX, y());
    }

    //������������ �� ���������
    int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    //����������� �� ������������� �����������
    if (collideWithSolid() == true)
    {
        //������� ������� � �������
        if (verticalSpeed > 0) {
            numberOfJumps = 2;
        }
        //����������� ������ �����
        if (verticalSpeed <= 0) {
            numberOfJumps = 0;
        }
        setPos(x(), oldY);
        verticalSpeed = 0;
    }
}

//�������� �� �������� � ������� ����������
bool Player::collideWithSolid()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Cell)) {
            if (((Cell*)(collisionList[i]))->isSolid == true) {
                return true;
            }
        }
    }
    return false;
}
