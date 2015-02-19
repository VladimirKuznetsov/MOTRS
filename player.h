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
    Player(QPixmap _spriteSheet, QObject * parent = 0);
    void setZoom(float _zoom);
    bool collideWithSolid();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //переменные для управления с мышки
    short targetX;
    Cell * targetCell;

    //переменные для взаимодействия с объектами
    QGraphicsPolygonItem * actionArea;
    QGraphicsPolygonItem * physicalArea;
    QString clues;

    //анимация
    float frame;
    float animationSpeed;
    QPixmap spriteSheet;

    //переменные состояния и направления
    float zoom;
    bool shiftIsPressed;
    signed int verticalSpeed;
    signed int horizontalSpeed;

    //константы скорости
    short JUMP_SPEED;
    short WALK_SPEED;
    short RUN_SPEED;
    short MAX_STEP_HEIGHT;

    //константы состояний
    enum Action {
        stand = 0,
        go,
        run,
        jump
    } action;

    //константы направлений
    enum Direction {
        right = 0,
        left
    } direction;

private:
    void flipHorizontal();

public slots:
    void move();
    void addClue(Cell * c);

signals:
    void investigating(Cell * c);
};

#endif // PLAYER_H
