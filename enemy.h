#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>

class Enemy : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent = 0);
    bool collideWithFloor();
    signed int verticalSpeed;
    signed int horizontalSpeed;
    unsigned int numberOfJumps;
    short HORIZONTAL_SPEED;
    short VERTICAL_SPEED;
public slots:
    void move();
    
};

#endif // ENEMY_H
