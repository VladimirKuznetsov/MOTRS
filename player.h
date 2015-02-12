#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QKeyEvent>
#include <QString>
#include <cell.h>
#include <float.h>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QString dir, QObject * parent = 0);
    bool collideWithSolid();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //���������� ��� �������������� � ���������
    QGraphicsPolygonItem * actionArea;
    QString clues;

    //��������
    float frame;
    float animationSpeed;
    QPixmap spriteSheet;

    //���������� ��������� � �����������
    char action;
    bool shiftIsPressed;
    char direction;
    signed int verticalSpeed;
    signed int horizontalSpeed;

    //��������� ��������
    short JUMP_SPEED;
    short WALK_SPEED;
    short RUN_SPEED;
    short MAX_STEP_HEIGHT;

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
    void addClue(Cell * c);

signals:
    void investigating(Cell * c);
};

#endif // PLAYER_H
