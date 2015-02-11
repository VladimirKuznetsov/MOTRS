#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>

class Cell : public QGraphicsPixmapItem
{
public:
    Cell(QString res, QGraphicsItem * parent = 0);
    void addInteraction(char _shortSymbol);
    void addInteraction(char _shortSymbol, char _cellToActivate);

    QPixmap spriteSheet;

    //������������ �������
    void setCellInactive();
    void setCellActive();
    void setCellActivated();

    //�����, ������������ �������� ������
    bool isSolid;
    bool isFloor;
    bool isInteractive;
    bool isGun;
    bool isTarget;
    bool isRechargeable;
    bool activatesCell;

    //���������� �����������
    char shortSymbol;
    char cellToActivate;


};

#endif // CELL_H
