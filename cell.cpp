#include "cell.h"
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QBrush>

//конструктор класса клетки
Cell::Cell(QString res, QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{
    //загружаем спрайтлист
    spriteSheet = QPixmap(res);

    //устанавливаем значения по умолчанию
    isSolid = false;
    isFloor = false;
    isInteractive = false;
    isGun = false;
    isTarget = false;
    isRechargeable = false;
    activatesCell = false;
    shortSymbol = ' ';
    cellToActivate = ' ';
    setCellInactive();
}

//установить неактивный режим
void Cell::setCellInactive()
{
    setPixmap(spriteSheet.copy(0, 0, 30, 30));
}

//установить активный режим (готов к взаимодействию)
void Cell::setCellActive()
{
    setPixmap(spriteSheet.copy(30, 0, 30, 30));
}

//установить режим после активации
void Cell::setCellActivated()
{
    setPixmap(spriteSheet.copy(60, 0, 30, 30));
}

//добавить возможность взаимодействия с игроком
void Cell::addInteraction(char _shortSymbol)
{
    shortSymbol = _shortSymbol;
    isInteractive = true;
}

//добавить возможность взаимодействия с игроком и другими клетками
void Cell::addInteraction(char _shortSymbol, char _cellToActivate)
{
    shortSymbol = _shortSymbol;
    cellToActivate = _cellToActivate;
    isInteractive = true;
    activatesCell = true;
}
