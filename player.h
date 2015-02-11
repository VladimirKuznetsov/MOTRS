#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QKeyEvent>
#include <QString>
#include <float.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QString dir, QGraphicsItem * parent = 0);
    bool collideWithSolid();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QGraphicsPolygonItem * actionArea;
    QString activatedItems;

    //анимация
    float frame;
    float animationSpeed;
    QPixmap spriteSheet;

    //переменные состояния и направления
    char action;
    bool shiftIsPressed;
    char direction;
    signed int verticalSpeed;
    signed int horizontalSpeed;

    //константы скорости
    short JUMP_SPEED;
    short WALK_SPEED;
    short RUN_SPEED;
    short MAX_STEP_HEIGHT;

    //константы состояний
    static const char ACT_STAND = 1;
    static const char ACT_GO = 2;
    static const char ACT_RUN = 3;
    static const char ACT_JUMP = 4;

    //константы направлений
    static const char DIR_LEFT = 1;
    static const char DIR_RIGHT = 2;

public slots:
    void move();
};

#endif // PLAYER_H
