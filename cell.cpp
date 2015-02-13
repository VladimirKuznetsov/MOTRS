#include "cell.h"
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QBrush>

//���������� �����������
Cell::Cell(QObject *parent)
{
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
}

//����������� �����������
Cell::Cell(QString res, int num, QObject * parent) : QObject(parent)
{
    //��������� ����������
    spSheet = QPixmap(res);

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
    setPixmap(spSheet.copy(spSheet.width() * num / 3, 0, spSheet.width()/3, spSheet.height()));
}

//���������� ���������� �����
void Cell::setCellInactive()
{
    isInteractive = false;
    setPixmap(spSheet.copy(0, 0, spSheet.width()/3, spSheet.height()));
}

//���������� �������� ����� (����� � ��������������)
void Cell::setCellActive()
{
    isInteractive = true;
    setPixmap(spSheet.copy(spSheet.width() / 3, 0, spSheet.width()/3, spSheet.height()));
}

//���������� ����� ����� ���������
void Cell::setCellActivated()
{
    //�������������� �������� �� ������ � ���� �����
    if (isRechargeable == true) return;

    isInteractive = false;
    setPixmap(spSheet.copy(spSheet.width() * 2 / 3, 0, spSheet.width()/3, spSheet.height()));
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
