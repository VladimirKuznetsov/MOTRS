#include "dialogBox.h"
#include <QTextCodec>
#include <QDebug>
#include <QPointF>
#include <QGraphicsRectItem>
#include <QColor>
#include <float.h>
#include "game.h"

extern Game * game;

//�����������
DialogBox::DialogBox(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));


    QGraphicsRectItem * back = new QGraphicsRectItem(-game->WINDOW_WIDTH / 2, - game->CELL_SIZE, \
                                                     game->WINDOW_WIDTH * 2, game->CELL_SIZE * 3, this);
    back->setBrush(QBrush(Qt::black));
    back->setOpacity(0.1);
    back->setFlag(QGraphicsItem::ItemStacksBehindParent);
    setDefaultTextColor(Qt::black);
    setFont(QFont("Arial", 16));
    mapToScene(20, 20);
    setVisible(false);
    isOn = false;

}

//��������� ����� �� ������� �����
void DialogBox::setDialog(QString _text[10])
{
    if (_text[0] == QString("") == true)
    {
        isOn = false;
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        text[i] = _text[i];
        if (text[i] == QString("")) break;
    }
    isOn = true;
    lineNumber = 0;
    setPlainText(text[lineNumber]);
    setVisible(true);
}

//��������� ����� �� ������
void DialogBox::setDialog(Cell *_cell)
{
    cell = _cell;
    setDialog(cell->interactionDialogue);
}

void DialogBox::move()
{
    QPointF textCoord;
    textCoord = game->mapToScene(QPoint(game->CELL_SIZE, game->CELL_SIZE / 2));
    setPos(textCoord);
}

//������� ������ �����
void DialogBox::nextLine()
{
    lineNumber++;
    setPlainText(text[lineNumber]);
    qDebug() << text[lineNumber];
    if (text[lineNumber] == QString(""))
    {
        isOn = false;

        if (cell) {
            emit interactionEnded(cell);
        }

        setVisible(false);
        return;
    }
}
