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
    verticalSpeed -= GRAVITY;

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

    //������ �� ���������
    game->followEnemy();
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

