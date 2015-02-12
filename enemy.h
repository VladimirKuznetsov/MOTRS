#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QString>
#include <float.h>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QString _dir, QObject * parent = 0);
    bool collideWithFloor();
    signed int verticalSpeed;
    signed int horizontalSpeed;
    unsigned int numberOfJumps;
    short HORIZONTAL_SPEED;
    short VERTICAL_SPEED;

    QString dir;
    float frame;
    float animationSpeed;
public slots:
    void move();
    
};

#endif // ENEMY_H
