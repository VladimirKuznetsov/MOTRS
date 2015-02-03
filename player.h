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
    void solveCollisions();
    signed int verticalSpeed;
    unsigned int horizontalSpeed;
    unsigned int numberOfJumps;
private:
    short JUMP_SPEED;
    short HORIZONTAL_SPEED;
    short GRAVITY;
public slots:
    void move();
};

#endif // PLAYER_H
