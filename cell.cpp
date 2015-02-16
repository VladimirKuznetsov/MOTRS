#include "cell.h"
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QBrush>

//упрощённый конструктор
Cell::Cell(QObject *parent)
{
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
}

//полноценный конструктор
Cell::Cell(QString res, int num, QObject * parent) : QObject(parent)
{
    //загружаем спрайтлист
    spSheet = QPixmap(res);

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
    setPixmap(spSheet.copy(spSheet.width() * num / 3, 0, spSheet.width()/3, spSheet.height()));
}

//установить неактивный режим
void Cell::setCellInactive()
{
    isInteractive = false;
    setPixmap(spSheet.copy(0, 0, spSheet.width()/3, spSheet.height()));
}

//установить активный режим (готов к взаимодействию)
void Cell::setCellActive()
{
    isInteractive = true;
    setPixmap(spSheet.copy(spSheet.width() / 3, 0, spSheet.width()/3, spSheet.height()));
}

//установить режим после активации
void Cell::setCellActivated()
{
    //перезаряжаемые предметы не входят в этот режим
    if (isRechargeable == true) return;

    isInteractive = false;
    setPixmap(spSheet.copy(spSheet.width() * 2 / 3, 0, spSheet.width()/3, spSheet.height()));
}

//добавить возможность взаимодействия с игроком
void Cell::addInteraction(char _shortSymbol)
{
    shortSymbol = _shortSymbol;
}

//добавить возможность взаимодействия с игроком и другими клетками
void Cell::addInteraction(char _shortSymbol, char _cellToActivate)
{
    shortSymbol = _shortSymbol;
    cellToActivate = _cellToActivate;
    activatesCell = true;
}
