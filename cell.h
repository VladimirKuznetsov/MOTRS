#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>

class Cell : public QGraphicsRectItem
{
public:
    Cell(QGraphicsItem * parent = 0);

    bool isSolid;
    bool isFloor;
    bool isInteractive;
    bool isGun;
    bool isTarget;
};

#endif // CELL_H
