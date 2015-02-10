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
Player::Player(QString dir, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    HORIZONTAL_SPEED = ceil(float(game->CELL_SIZE) / 5);

    frame = 0;
    animationSpeed = 0.3;
    shiftIsPressed = false;
    action = ACT_STAND;
    direction = DIR_RIGHT;

    spriteSheet = QPixmap(dir);
    setPixmap(spriteSheet.copy(0, 0, 50, 90));
    //setTransformOriginPoint(boundingRect().width() / 2, 0);

    horizontalSpeed = 0;
    verticalSpeed = 0;
}

//�������� ������
void Player::move()
{
    //��������
    frame += animationSpeed;
    if (action == ACT_STAND) setPixmap((spriteSheet.copy(0, 0, 50, 90)));
    if (action == ACT_JUMP) setPixmap((spriteSheet.copy(50, 0, 50, 90)));
    if (action == ACT_GO) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 90, 50, 90));
    if (action == ACT_RUN) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 180, 50, 90));

    //������������ �� ���������
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    if (collideWithSolid() == true)
    {
        //����������� ������ �����
        if (verticalSpeed <= 0) {
            if (horizontalSpeed == 0) action = ACT_STAND;
            else if (shiftIsPressed == true) action = ACT_RUN;
            else action = ACT_GO;
        }
    }

    //����������� �� ������������� �����������
    while (collideWithSolid() == true)
    {
        if (verticalSpeed != 0) setPos(x(), y() - verticalSpeed);
        else setPos(x(), y() - 1);
        verticalSpeed = 0;
    }

    //������������ �� �����������
    setPos(x() + horizontalSpeed, y());

    //����������� �� ��������������� �����������
    while (collideWithSolid() == true)
    {
        if (horizontalSpeed != 0) setPos(x() - horizontalSpeed, y());
        else setPos(x() - 1, y());
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

//��������� ������� �������
void Player::keyPressEvent(QKeyEvent *event)
{

    //�������� ������ ��� �����
    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_Left))
    {
        if (action == ACT_STAND)
        {
            //����� ��� ������� shift
            if (shiftIsPressed == true)
            {
                action = ACT_RUN;
            //��� ��� ������� shift
            } else {
                action = ACT_GO;
            }
        }

        //�������� ����������� ��������
        if ((event->key() == Qt::Key_Right) && (direction == DIR_LEFT))
        {
            setOffset(-boundingRect().width() / 2, 0);
            scale(-1, 1);
            direction = DIR_RIGHT;
        }

        if ((event->key() == Qt::Key_Left) && (direction == DIR_RIGHT))
        {
            setOffset(-boundingRect().width() / 2, 0);
            scale(-1, 1);
            direction = DIR_LEFT;
        }

        //�������� �������� ��������
        horizontalSpeed = HORIZONTAL_SPEED * (shiftIsPressed + 1) * pow(-1, (direction == DIR_RIGHT) + 1);
    }

    //�������, ���� ��� ��������
    if ((event->key() == Qt::Key_Up) && (action != ACT_JUMP))
    {
        action = ACT_JUMP;
        verticalSpeed = JUMP_SPEED;
    }

    //��������� ��������
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = true;

        //��������� �� ���
        if (action == ACT_GO)
        {
            action = ACT_RUN;
            horizontalSpeed = HORIZONTAL_SPEED * 2;
        }
    }
}

//��������� ���������� �������
void Player::keyReleaseEvent(QKeyEvent *event)
{

    //���������� ��������
    if (((event->key() == Qt::Key_Left) && (direction == DIR_LEFT)) || \
            ((event->key() == Qt::Key_Right) && (direction == DIR_RIGHT)))
    {
        horizontalSpeed = 0;

        //���������������, ���� ����� �� � ������
        if ((action == ACT_GO) || (action == ACT_RUN)) {
            action = ACT_STAND;
        }
    }

    //���������� ��������
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = false;

        //��������� �� ���
        if (action == ACT_RUN)
        {
            action = ACT_GO;
            horizontalSpeed = HORIZONTAL_SPEED;
        }
    }
}
