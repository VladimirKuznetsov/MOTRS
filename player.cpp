#include "player.h"
#include "cell.h"
//#include <QDebug>
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

//конструктор
Player::Player(QPixmap _spriteSheet, QObject *parent) : QObject(parent)
{
    clues = "";

    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    WALK_SPEED = ceil(float(game->CELL_SIZE) / 8);
    RUN_SPEED = ceil(float(game->CELL_SIZE) / 5);
    MAX_STEP_HEIGHT = ceil(float(game->CELL_SIZE) / 3);
    zoom = 1.0;

    frame = 0;
    animationSpeed = 0.3;
    shiftIsPressed = false;
    action = ACT_STAND;
    direction = DIR_RIGHT;

    spriteSheet = _spriteSheet;
    setPixmap(spriteSheet.copy(0, 0, 50, 90));
    QVector <QPointF> areaCorners;

    //создаём полигон, ограничивающий область действия
    areaCorners << QPointF(0, 0) << QPointF(boundingRect().width() * 3 / 2, 0) \
                   << QPointF(boundingRect().width() * 3 / 2, boundingRect().height()) \
                      << QPointF(0, boundingRect().height());

    actionArea = new QGraphicsPolygonItem(QPolygonF(areaCorners), this);
    actionArea->setVisible(false);
    horizontalSpeed = 0;
    verticalSpeed = 0;
}

//установить зум
void Player::setZoom(float _zoom)
{
    zoom = _zoom;
    JUMP_SPEED *= zoom;
    WALK_SPEED *= zoom;
    RUN_SPEED *= zoom;
    MAX_STEP_HEIGHT *= zoom;
}

//перемещения игрока
void Player::move()
{
    //смена кадров анимации
    frame += animationSpeed;
    if (action == ACT_STAND) setPixmap((spriteSheet.copy(0, 0, 50, 90)));
    if (action == ACT_JUMP) setPixmap((spriteSheet.copy(50, 0, 50, 90)));
    if (action == ACT_GO) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 90, 50, 90));
    if (action == ACT_RUN) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 180, 50, 90));

    //разрешение колиизий анимации
    while (collideWithSolid() == true)
    {
        if (collideWithSolid() == true) setPos(x(), y() - 1);
        if (collideWithSolid() == true) setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

    //перемещение по вертикали
    unsigned int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= (game->GRAVITY * zoom);

    if (collideWithSolid() == true)
    {
        //приземляемся на пол
        if (verticalSpeed < 0) {
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

    //разрешение колиизий при вертикальном перемещении
    if (collideWithSolid() == true)
    {
        while (collideWithSolid() == true)
        {
            setPos(x(), y() - pow(-1, (verticalSpeed < 0) + 1));
        }

        //ограничиваем максимальную высоту ступеньки, доступную персонажу
        if (abs(y() - oldY) > MAX_STEP_HEIGHT)  setPos(x(), oldY);

        verticalSpeed = 0;
    }

    //перемещение по горизонтали
    setPos(x() + horizontalSpeed, y());

    //разрешение колиизий при горизонтальном перемещении
    while (collideWithSolid() == true)
    {
        setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

}

//обновляем список найденных улик
void Player::addClue(Cell * c)
{
    if (clues.contains(c->shortSymbol, Qt::CaseSensitive) == false)
    {
        clues.append(c->shortSymbol);
    }
}

//определяем коллизии с твёрдыми объектами
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

//обработка нажатия клавиши
void Player::keyPressEvent(QKeyEvent *event)
{
    //попытка взаимодействия
    if (event->key() == Qt::Key_Space)
    {
        QList <QGraphicsItem *> availableItems = actionArea->collidingItems();
        for (int i = 0; i < availableItems.size(); i++) {

            //находим интеракивные объекты окружения
            if ((typeid(*availableItems[i]) == typeid(Cell)) && (((Cell*)availableItems[i])->isInteractive == true)) {

                //останавливаемся для взаимодействия
                horizontalSpeed = 0;

                //переводим объект в состояние "активирован"
                Cell * c = dynamic_cast<Cell *>(availableItems[i]);
                c->setCellActivated();

                //отправляем сигнал для отображения диалога
                emit investigating(c);

                //взаимодействуем только с одним объектом за нажатие
                break;
            }
        }
    }

    //движемся вправо
    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_Left))
    {
        if (action == ACT_STAND)
        {
            //бег
            if (shiftIsPressed == true)
            {
                action = ACT_RUN;
            //шаг
            } else {
                action = ACT_GO;
            }
        }

        //при смене направления, отражаем объект по горизонтали
        if ((event->key() == Qt::Key_Right) && (direction == DIR_LEFT))
        {
            frame = 0;
            flipHorizontal();
            direction = DIR_RIGHT;
        }

        if ((event->key() == Qt::Key_Left) && (direction == DIR_RIGHT))
        {
            frame = 0;
            flipHorizontal();
            direction = DIR_LEFT;
        }

        if (shiftIsPressed == true) horizontalSpeed = RUN_SPEED;
        else horizontalSpeed = WALK_SPEED;

        horizontalSpeed *= pow(-1, (direction == DIR_RIGHT) + 1);
    }

    //прыжок
    if ((event->key() == Qt::Key_Up) && (action != ACT_JUMP))
    {
        frame = 0;
        action = ACT_JUMP;
        verticalSpeed = JUMP_SPEED;
    }

    //ускорение
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

//отрабатываем отпускание клавиши
void Player::keyReleaseEvent(QKeyEvent *event)
{
    //прекращаем движение по горизонтали
    if (((event->key() == Qt::Key_Left) && (direction == DIR_LEFT)) || \
            ((event->key() == Qt::Key_Right) && (direction == DIR_RIGHT)))
    {
        horizontalSpeed = 0;

        //остановка
        if ((action == ACT_GO) || (action == ACT_RUN)) {
            action = ACT_STAND;
        }
    }

    //замедляем движение
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

//отражаем объект по горизонтали
void Player::flipHorizontal()
{
    // Get the current transform
    QTransform transform(this->transform());

    qreal m11 = transform.m11();    // Horizontal scaling
    qreal m12 = transform.m12();    // Vertical shearing
    qreal m13 = transform.m13();    // Horizontal Projection
    qreal m21 = transform.m21();    // Horizontal shearing
    qreal m22 = transform.m22();    // vertical scaling
    qreal m23 = transform.m23();    // Vertical Projection
    qreal m31 = transform.m31();    // Horizontal Position (DX)
    qreal m32 = transform.m32();    // Vertical Position (DY)
    qreal m33 = transform.m33();    // Addtional Projection Factor

    // We need this in a minute
    qreal scale = m11;

    // Horizontal flip
    m11 = -m11;

    // Re-position back to origin
    if(m31 > 0)
        m31 = 0;
    else
        m31 = (boundingRect().width() * scale);

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    setTransform(transform);
}
