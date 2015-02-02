#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Player();
    void keyPressEvent(QKeyEvent *event);
    signed int verticalSpeed;
    unsigned int horizontalSpeed;
    unsigned int jumps;
public slots:
    void move();
};

#endif // PLAYER_H
