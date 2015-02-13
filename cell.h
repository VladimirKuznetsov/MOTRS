#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>

class Cell : public QObject, public QGraphicsPixmapItem
{
public:
    Cell(QObject * parent = 0);
    Cell(QString res, int num, QObject * parent = 0);
    void addInteraction(char _shortSymbol);
    void addInteraction(char _shortSymbol, char _cellToActivate);

    QPixmap spSheet;

    //переключение режимов
    void setCellInactive();
    void setCellActive();
    void setCellActivated();

    //флаги, определ€ющие свойства клетки
    bool isSolid;
    bool isFloor;
    bool isInteractive;
    bool isGun;
    bool isTarget;
    bool isRechargeable;
    bool activatesCell;

    //символьные обозначени€
    char shortSymbol;
    char cellToActivate;

    //диалог, отображаемый при исследовании
    QString interactionDialogue[10];

};

#endif // CELL_H
