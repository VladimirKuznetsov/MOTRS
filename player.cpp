#include "player.h"
#include "cell.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include <math.h>
#include <float.h>
#include <game.h>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

extern Game * game;

//конструктор класса
Player::Player(QString dir, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    clues = "";

    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    WALK_SPEED = ceil(float(game->CELL_SIZE) / 8);
    RUN_SPEED = ceil(float(game->CELL_SIZE) / 5);
    MAX_STEP_HEIGHT = ceil(float(game->CELL_SIZE) / 3);

    frame = 0;
    animationSpeed = 0.3;
    shiftIsPressed = false;
    action = ACT_STAND;
    direction = DIR_RIGHT;

    spriteSheet = QPixmap(dir);
    setPixmap(spriteSheet.copy(0, 0, 50, 90));
    QVector <QPointF> areaCorners;
    //описываем область действий игрока
    areaCorners << QPointF(0, 0) << QPointF(boundingRect().width() * 3 / 2, 0) \
                   << QPointF(boundingRect().width() * 3 / 2, boundingRect().height()) \
                      << QPointF(0, boundingRect().height());

    actionArea = new QGraphicsPolygonItem(QPolygonF(areaCorners), this);
    actionArea->setVisible(false);
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

    //разрешаем коллизии анимации
    while (collideWithSolid() == true)
    {
        if (collideWithSolid() == true) setPos(x(), y() - 1);
        if (collideWithSolid() == true) setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

    //перемещаемся по вертикали
    unsigned int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    if (collideWithSolid() == true)
    {
        //провалились сквозь землю
        if (verticalSpeed <= 0) {
            if (horizontalSpeed == 0) action = ACT_STAND;
            else if (shiftIsPressed == true) {
                action = ACT_RUN;
                horizontalSpeed = RUN_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
            } else
            {
                action = ACT_GO;
                horizontalSpeed = WALK_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
            }
        }
    }

    //ограничение по вертикальному перемещению
    if (collideWithSolid() == true)
    {
        while (collideWithSolid() == true)
        {
            setPos(x(), y() - pow(-1, (verticalSpeed <= 0) + 1));
        }

        //не позволяем персонажу карабкаться на высокие препятствия
        if (abs(y() - oldY) > MAX_STEP_HEIGHT)  setPos(x(), oldY);

        verticalSpeed = 0;
    }

    //перемещаемся по горизонтали
    setPos(x() + horizontalSpeed, y());

    //ограничение по горизонтальному перемещению
    while (collideWithSolid() == true)
    {
        setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

}

//регистрируем взаимодействие в списке
void Player::addClue(Cell * c)
{
    if (clues.contains(c->shortSymbol, Qt::CaseSensitive) == false)
    {
        clues.append(c->shortSymbol);
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
    //взаимодействие
    if (event->key() == Qt::Key_Space)
    {
        QList <QGraphicsItem *> availableItems = actionArea->collidingItems();
        for (int i = 0; i < availableItems.size(); i++) {

            //обнаруживаем интерактивную клетку в поле действия
            if ((typeid(*availableItems[i]) == typeid(Cell)) && (((Cell*)availableItems[i])->isInteractive == true)) {

                //останавливаемся для взаимодействия
                horizontalSpeed = 0;

                //переключаем объект в режим "активирован"
                Cell * c = dynamic_cast<Cell *>(availableItems[i]);
                c->setCellActivated();

                //отображаем диалог
                emit investigating(c);

                //взаимодействуем с одной клеткой за раз
                break;
            }
        }
    }

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
            frame = 0;
            setOffset(-boundingRect().width() / 4, 0);
            scale(-1, 1);
            direction = DIR_RIGHT;
        }

        if ((event->key() == Qt::Key_Left) && (direction == DIR_RIGHT))
        {
            frame = 0;
            setOffset(-boundingRect().width() / 4, 0);
            scale(-1, 1);
            direction = DIR_LEFT;
        }

        //изменяем скорость движения
        if (shiftIsPressed == true) horizontalSpeed = RUN_SPEED;
        else horizontalSpeed = WALK_SPEED;

        horizontalSpeed *= pow(-1, (direction == DIR_RIGHT) + 1);
    }

    //прыгаем, если это возможно
    if ((event->key() == Qt::Key_Up) && (action != ACT_JUMP))
    {
        frame = 0;
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
            horizontalSpeed = RUN_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
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
            horizontalSpeed = WALK_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
        }
    }
}
