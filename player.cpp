#include "player.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>

//����������� ������
Player::Player()
{
    verticalSpeed = 0;
    horizontalSpeed = 5;
    jumps = 2;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(30);
}

//���������� ������� �������
void Player::keyPressEvent(QKeyEvent *event)
{
    //������ �� ������� �� ������
    if ((event->key() == Qt::Key_Space) & (jumps < 2)) {
        jumps++;
        verticalSpeed = (16/jumps);
    }

}

//�������� ������
void Player::move()
{
    setPos(x() + horizontalSpeed, y() - verticalSpeed);
    verticalSpeed -= 1;

    //����������� �� ������������� �����������
    if(pos().y() >= scene()->sceneRect().height() - rect().height()) {
        jumps = 0;
        verticalSpeed = 0;
        setPos(x(), scene()->sceneRect().height() - rect().height());
    }
}
