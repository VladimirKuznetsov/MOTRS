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

    //������, ������������ ��� ������������
    QString interactionDialogue[10];

};

#endif // CELL_H
