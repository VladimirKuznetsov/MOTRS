#include "dialogBox.h"
#include <QTextCodec>
#include <QDebug>
#include <QPointF>
#include <QGraphicsRectItem>
#include <QColor>
#include <float.h>
#include "game.h"

extern Game * game;

//конструктор
DialogBox::DialogBox(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));


    QGraphicsRectItem * back = new QGraphicsRectItem(-game->WINDOW_WIDTH / 2, - game->CELL_SIZE, \
                                                     game->WINDOW_WIDTH * 2, game->CELL_SIZE * 3, this);
    back->setBrush(QBrush(Qt::black));
    back->setOpacity(0.2);
    back->setFlag(QGraphicsItem::ItemStacksBehindParent);
    setDefaultTextColor(Qt::white);
    setFont(QFont("Calibri", 22));
    setVisible(false);
    isOn = false;

}

//загружаем текст из массива строк
void DialogBox::setDialog(QString _text[10])
{
    for (int i = 0; i < 10; i++)
    {
        text[i] = _text[i];
        if (text[i] == QString("")) break;
    }

    isOn = true;
    lineNumber = 0;
    setPlainText(text[lineNumber]);
    setVisible(true);

    //если массив пуст, пропускаем диалог
    if (text[0] == QString("")) skip();
}

//загружаем текст из клетки
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

//листаем диалог вперёд
void DialogBox::nextLine()
{
    lineNumber++;
    if ((text[lineNumber] == QString("")) || (lineNumber == 9))
    {
        isOn = false;

        if ((cell) && (cell->shortSymbol != ' ')) {
            emit dialogEnded(cell);
            cell->shortSymbol = ' ';
        } else
        {
            emit dialogEnded();
        }

        setVisible(false);
        return;
    }
    setPlainText(text[lineNumber]);
}

//пропуск диалога
void DialogBox::skip()
{
    lineNumber = 8;
    nextLine();
}
