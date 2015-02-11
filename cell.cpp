#include "cell.h"
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QBrush>

//����������� ������ ������
Cell::Cell(QString res, QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{
    //��������� ����������
    spriteSheet = QPixmap(res);

    //������������� �������� �� ���������
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

//���������� ���������� �����
void Cell::setCellInactive()
{
    setPixmap(spriteSheet.copy(0, 0, 30, 30));
}

//���������� �������� ����� (����� � ��������������)
void Cell::setCellActive()
{
    setPixmap(spriteSheet.copy(30, 0, 30, 30));
}

//���������� ����� ����� ���������
void Cell::setCellActivated()
{
    setPixmap(spriteSheet.copy(60, 0, 30, 30));
}

//�������� ����������� �������������� � �������
void Cell::addInteraction(char _shortSymbol)
{
    shortSymbol = _shortSymbol;
    isInteractive = true;
}

//�������� ����������� �������������� � ������� � ������� ��������
void Cell::addInteraction(char _shortSymbol, char _cellToActivate)
{
    shortSymbol = _shortSymbol;
    cellToActivate = _cellToActivate;
    isInteractive = true;
    activatesCell = true;
}
