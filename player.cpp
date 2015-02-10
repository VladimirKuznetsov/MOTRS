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

//конструктор класса
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

//движение игрока
void Player::move()
{
    //анимация
    frame += animationSpeed;
    if (action == ACT_STAND) setPixmap((spriteSheet.copy(0, 0, 50, 90)));
    if (action == ACT_JUMP) setPixmap((spriteSheet.copy(50, 0, 50, 90)));
    if (action == ACT_GO) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 90, 50, 90));
    if (action == ACT_RUN) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 180, 50, 90));

    //перемещаемся по вертикали
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    if (collideWithSolid() == true)
    {
        //провалились сквозь землю
        if (verticalSpeed <= 0) {
            if (horizontalSpeed == 0) action = ACT_STAND;
            else if (shiftIsPressed == true) action = ACT_RUN;
            else action = ACT_GO;
        }
    }

    //ограничение по вертикальному перемещению
    while (collideWithSolid() == true)
    {
        if (verticalSpeed != 0) setPos(x(), y() - verticalSpeed);
        else setPos(x(), y() - 1);
        verticalSpeed = 0;
    }

    //перемещаемся по горизонтали
    setPos(x() + horizontalSpeed, y());

    //ограничение по горизонтальному перемещению
    while (collideWithSolid() == true)
    {
        if (horizontalSpeed != 0) setPos(x() - horizontalSpeed, y());
        else setPos(x() - 1, y());
    }
}

//проверка на коллизии с твёрдыми предметами
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

//отработка нажатия клавиши
void Player::keyPressEvent(QKeyEvent *event)
{

    //движемся вправо или влево
    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_Left))
    {
        if (action == ACT_STAND)
        {
            //бежим при нажатии shift
            if (shiftIsPressed == true)
            {
                action = ACT_RUN;
            //идём без нажатия shift
            } else {
                action = ACT_GO;
            }
        }

        //изменяем направление движения
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

        //изменяем скорость движения
        horizontalSpeed = HORIZONTAL_SPEED * (shiftIsPressed + 1) * pow(-1, (direction == DIR_RIGHT) + 1);
    }

    //прыгаем, если это возможно
    if ((event->key() == Qt::Key_Up) && (action != ACT_JUMP))
    {
        action = ACT_JUMP;
        verticalSpeed = JUMP_SPEED;
    }

    //ускорение движения
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = true;

        //переходим на бег
        if (action == ACT_GO)
        {
            action = ACT_RUN;
            horizontalSpeed = HORIZONTAL_SPEED * 2;
        }
    }
}

//отработка отпускания клавиши
void Player::keyReleaseEvent(QKeyEvent *event)
{

    //прекращаем движение
    if (((event->key() == Qt::Key_Left) && (direction == DIR_LEFT)) || \
            ((event->key() == Qt::Key_Right) && (direction == DIR_RIGHT)))
    {
        horizontalSpeed = 0;

        //останавливаемся, если игрок не в прыжке
        if ((action == ACT_GO) || (action == ACT_RUN)) {
            action = ACT_STAND;
        }
    }

    //замедление движения
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = false;

        //переходим на шаг
        if (action == ACT_RUN)
        {
            action = ACT_GO;
            horizontalSpeed = HORIZONTAL_SPEED;
        }
    }
}
