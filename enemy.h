#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItem>
#include <QString>
#include <float.h>
#include<QTime>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QPixmap _spriteSheet, QObject * parent = 0);
    bool collideWithFloor();
    QPixmap spriteSheet;
    signed int verticalSpeed;
    signed int horizontalSpeed;
    unsigned int numberOfJumps;
    short HORIZONTAL_SPEED;
    short VERTICAL_SPEED;

    float frame;
    float animationSpeed;

    QTime * time;

public slots:
    void move();
    
};

#endif // ENEMY_H
