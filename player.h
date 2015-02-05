#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Player(QGraphicsItem * parent = 0);
    void jump();
    void right();
    void left();
    bool collideWithSolid();
    signed int verticalSpeed;
    signed int horizontalSpeed;
    unsigned int numberOfJumps;
    short JUMP_SPEED;
    short HORIZONTAL_SPEED;
public slots:
    void move();
};

#endif // PLAYER_H
