#include "cell.h"

Cell::Cell(QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    isSolid = false;
    isFloor = false;
    isInteractive = false;
    isGun = false;
    isTarget = false;
}
