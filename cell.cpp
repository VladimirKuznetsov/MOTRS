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
    isInteractive = false;
    setPixmap(spriteSheet.copy(0, 0, 30, 30));
}

//���������� �������� ����� (����� � ��������������)
void Cell::setCellActive()
{
    isInteractive = true;
    setPixmap(spriteSheet.copy(30, 0, 30, 30));
}

//���������� ����� ����� ���������
void Cell::setCellActivated()
{
    //�������������� �������� �� ������ � ���� �����
    if (isRechargeable == true) return;

    isInteractive = false;
    setPixmap(spriteSheet.copy(60, 0, 30, 30));
}

//�������� ����������� �������������� � �������
void Cell::addInteraction(char _shortSymbol)
{
    shortSymbol = _shortSymbol;
}

//�������� ����������� �������������� � ������� � ������� ��������
void Cell::addInteraction(char _shortSymbol, char _cellToActivate)
{
    shortSymbol = _shortSymbol;
    cellToActivate = _cellToActivate;
    activatesCell = true;
}
