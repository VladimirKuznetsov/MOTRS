#ifndef SOLID_H
#define SOLID_H

#include <QGraphicsRectItem>

class Solid : public QGraphicsRectItem
{
public:
    Solid(QGraphicsItem * parent = 0);

    char kind;
    static const char KindFloor = 1;
    static const char KindObstacle = 2;
};

#endif // SOLID_H
