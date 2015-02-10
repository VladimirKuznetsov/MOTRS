#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QString>
#include <float.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QString dir, QGraphicsItem * parent = 0);
    void jump();
    void right();
    void left();
    bool collideWithSolid();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    signed int verticalSpeed;
    signed int horizontalSpeed;

    //��������
    float frame;
    float animationSpeed;
    QPixmap spriteSheet;

    //���������� ��������� � �����������
    char action;
    bool shiftIsPressed;
    char direction;

    //��������� ��������
    short JUMP_SPEED;
    short HORIZONTAL_SPEED;

    //��������� ���������
    static const char ACT_STAND = 1;
    static const char ACT_GO = 2;
    static const char ACT_RUN = 3;
    static const char ACT_JUMP = 4;

    //��������� �����������
    static const char DIR_LEFT = 1;
    static const char DIR_RIGHT = 2;

public slots:
    void move();
};

#endif // PLAYER_H
