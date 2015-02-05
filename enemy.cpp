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
    //������������ �� �����������
    setPos(x() + horizontalSpeed, y());

    //����������� �� ��������������� �����������
    if (collideWithFloor() == true)
    {
        //������� ������
        if (horizontalSpeed >= 0) {
            do {
                setPos(x() - 1, y());
            } while (collideWithFloor() == true);
        }
        //������� �����
        if (horizontalSpeed < 0) {
            do {
                setPos(x() + 1, y());
            } while (collideWithFloor() == true);
        }
    }

    //������� ������
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

    //������������ �� ���������
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    //����������� �� ������������� �����������
    if (collideWithFloor() == true)
    {
        //������� ������� � �������
        if (verticalSpeed > 0) {
            do {
                setPos(x(), y() + 1);
            } while (collideWithFloor() == true);
        }
        //����������� ������ �����
        if (verticalSpeed <= 0) {
            do {
                setPos(x(), y() - 1);
            } while (collideWithFloor() == true);
        }
        verticalSpeed = 0;
    }
}

//�������� �� �������� � ������� ����������
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

