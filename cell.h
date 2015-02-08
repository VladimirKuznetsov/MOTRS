#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QString>

class Cell : public QGraphicsPixmapItem
{
public:
    Cell(QString res, QGraphicsItem * parent = 0);

    bool isSolid;
    bool isFloor;
    bool isInteractive;
    bool isGun;
    bool isTarget;
};

#endif // CELL_H
