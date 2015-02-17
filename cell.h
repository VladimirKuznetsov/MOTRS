#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>

class Cell : public QObject, public QGraphicsPixmapItem
{
public:
    Cell(QString res, int num, QObject * parent);   //УДАЛИТЬ

    Cell(QObject * parent = 0);
    void addInteraction(char _shortSymbol);
    void addInteraction(char _shortSymbol, char _cellToActivate);

    void setPicInactive(QPixmap _pic);
    void setPicActive(QPixmap _pic);
    void setPicActivated(QPixmap _pic);

    QPixmap picInactive;
    QPixmap picActive;
    QPixmap picActivated;

    QPixmap spSheet;    //УДАЛИТЬ

    //переключение режимов
    void setCellInactive();
    void setCellActive();
    void setCellActivated();

    //флаги, определяющие свойства клетки
    bool isSolid;
    bool isFloor;
    bool isInteractive;
    bool isGun;
    bool isTarget;
    bool isRechargeable;
    bool activatesCell;

    //символьные обозначения
    char shortSymbol;
    char cellToActivate;

    //диалог, отображаемый при исследовании
    QString interactionDialogue[10];

};

#endif // CELL_H
