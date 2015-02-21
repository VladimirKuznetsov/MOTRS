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

//конструктор
Player::Player(QPixmap _spriteSheet, QObject *parent) : QObject(parent)
{
    clues = "";
    targetX = -1;
    targetCell = new Cell();

    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    WALK_SPEED = ceil(float(game->CELL_SIZE) / 8);
    RUN_SPEED = ceil(float(game->CELL_SIZE) / 5);
    MAX_STEP_HEIGHT = ceil(float(game->CELL_SIZE) / 3);
    zoom = 1.0;

    qDebug() << QString("walk speed = ") + QString::number(WALK_SPEED);
    frame = 0;
    animationSpeed = 0.3;
    shiftIsPressed = false;
    action = stand;
    direction = right;

    spriteSheet = _spriteSheet;
    setPixmap(spriteSheet.copy(0, 0, 50, 90));
    QVector <QPointF> areaCorners;



    //создаём полигон, ограничивающий область коллизий
    areaCorners << QPointF(0, 0) << QPointF(boundingRect().width(), 0) \
                   << QPointF(boundingRect().width(), boundingRect().height()) \
                      << QPointF(0, boundingRect().height());

    physicalArea = new QGraphicsPolygonItem(QPolygonF(areaCorners), this);
    physicalArea->setOpacity(0);

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
    static unsigned int i = 0;
    qDebug() << QString::number(i);
    //смена кадров анимации
    frame += animationSpeed;
    if (action == stand) setPixmap((spriteSheet.copy(0, 0, 50, 90)));
    if (action == jump) setPixmap((spriteSheet.copy(50, 0, 50, 90)));
    if (action == go) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 90, 50, 90));
    if (action == run) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 180, 50, 90));

    //разрешение колиизий анимации
    while (collideWithSolid() == true)
    {
        if (collideWithSolid() == true) setPos(x(), y() - 1);
        if (collideWithSolid() == true) setPos(x() - pow(-1, (direction == right) + 1), y());
    }

    //перемещение по вертикали
    unsigned int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= (game->GRAVITY * zoom);

    if (collideWithSolid() == true)
    {
        //приземляемся на пол
        if (verticalSpeed < 0) {
            if (horizontalSpeed == 0) action = stand;
            else if (shiftIsPressed == true) {
                action = run;
                horizontalSpeed = RUN_SPEED * pow(-1, (direction == right) + 1);
            } else
            {
                action = go;
                horizontalSpeed = WALK_SPEED * pow(-1, (direction == right) + 1);
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

    //проверяем на столкновение с препятствием
    QList <QGraphicsItem *> collisions = collidingItems();
    for (int i = 0; i < collisions.size(); i++)
    {
        if ((typeid(*collisions[i]) == typeid(Cell)) && \
                (((Cell*)collisions[i])->isFloor == false) && (((Cell*)collisions[i])->isSolid == true))
        {
            targetCell = new Cell();
            targetX = -1;
            QKeyEvent * event = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Left, 0, "", false, 1);
            keyReleaseEvent(event);
            *event = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Right, 0, "", false, 1);
            keyReleaseEvent(event);
            *event = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Shift, 0, "", false, 1);
            keyReleaseEvent(event);
        }
    }

    //разрешение колиизий при горизонтальном перемещении
    while (collideWithSolid() == true)
    {
        setPos(x() - pow(-1, (direction == right) + 1), y());
    }

    //персонаж достиг цели движения
    if (actionArea->collidesWithItem(targetCell))
    {
        targetCell->setCellActivated();
        emit investigating(targetCell);
        targetCell = new Cell();
        QKeyEvent * keyEvent = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Left, 0, "", false, 1);
        keyReleaseEvent(keyEvent);
        *keyEvent = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Right, 0, "", false, 1);
        keyReleaseEvent(keyEvent);
        *keyEvent = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Shift, 0, "", false, 1);
        keyReleaseEvent(keyEvent);
    }

    //персонаж достиг цели движения
    if (physicalArea->contains(mapFromScene(targetX, y())))
    {
        QKeyEvent * event = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Left, 0, "", false, 1);
        keyReleaseEvent(event);
        *event = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Right, 0, "", false, 1);
        keyReleaseEvent(event);
        *event = QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Shift, 0, "", false, 1);
        keyReleaseEvent(event);

        //если до объекта необходимо допрыгнуть
        if ((targetCell->shortSymbol != ' ') && (targetCell->y() + targetCell->boundingRect().width() < y()))
        {
            *event = QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Up, 0, "", false, 1);
            keyPressEvent(event);
        }
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
        if (action == stand)
        {
            //бег
            if (shiftIsPressed == true)
            {
                action = run;
            //шаг
            } else {
                action = go;
            }
        }

        //при смене направления, отражаем объект по горизонтали
        if ((event->key() == Qt::Key_Right) && (direction == left))
        {
            frame = 0;
            flipHorizontal();
            direction = right;
        }

        if ((event->key() == Qt::Key_Left) && (direction == right))
        {
            frame = 0;
            flipHorizontal();
            direction = left;
        }

        if (shiftIsPressed == true) horizontalSpeed = RUN_SPEED;
        else horizontalSpeed = WALK_SPEED;

        horizontalSpeed *= pow(-1, (direction == right) + 1);
    }

    //прыжок
    if ((event->key() == Qt::Key_Up) && (!event->isAutoRepeat()) && (action != jump))
    {
        frame = 0;
        action = jump;
        verticalSpeed = JUMP_SPEED;
    }

    //ускорение
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = true;

        //переходим на бег
        if (action == go)
        {
            action = run;
            horizontalSpeed = RUN_SPEED * pow(-1, (direction == right) + 1);
        }
    }
}

//отрабатываем отпускание клавиши
void Player::keyReleaseEvent(QKeyEvent *event)
{
    //прекращаем движение по горизонтали
    if (((event->key() == Qt::Key_Left) && (direction == left)) || \
            ((event->key() == Qt::Key_Right) && (direction == right)))
    {
        horizontalSpeed = 0;

        //остановка
        if ((action == go) || (action == run)) {
            action = stand;
        }
    }

    //замедляем движение
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = false;

        //переходим на шаг
        if (action == run)
        {
            action = go;
            horizontalSpeed = WALK_SPEED * pow(-1, (direction == right) + 1);
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
