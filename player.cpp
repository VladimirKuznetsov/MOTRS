#include "player.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

//конструктор класса
Player::Player()
{
    verticalSpeed = 0;
    horizontalSpeed = 5;
    jumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//обработака нажатия клавиши
void Player::keyPressEvent(QKeyEvent *event)
{
    //прыжок по нажатию на пробел
    if ((event->key() == Qt::Key_Space) & (jumps < 2)) {
        jumps++;
        verticalSpeed = (16/jumps);
    }

}

//движение игрока
void Player::move()
{
    setPos(x() + horizontalSpeed, y() - verticalSpeed);
    verticalSpeed -= 1;

    //ограничение по вертикальному перемещению
    if(pos().y() >= scene()->sceneRect().height() - rect().height()) {
        jumps = 0;
        verticalSpeed = 0;
        setPos(x(), scene()->sceneRect().height() - rect().height());
    }
}
