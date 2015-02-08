#include "cell.h"
#include <QPixmap>

Cell::Cell(QString res, QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(res));
    isSolid = false;
    isFloor = false;
    isInteractive = false;
    isGun = false;
    isTarget = false;
}
