#include "levelIntro.h"
#include <QGraphicsTextItem>
#include "game.h"

extern Game * game;

LevelIntro::LevelIntro(QGraphicsView *parent) : Level(parent)
{
    step = 0;
}

void LevelIntro::init(QString map[])
{
    zoom = 1;

    //отрисовываем фон
    QStringList colors = map[2].split(' ');
    setBackgroundBrush(QBrush(QColor(colors[0].toInt(), colors[1].toInt(), colors[2].toInt())));

    //название игры
    QGraphicsTextItem * title = new QGraphicsTextItem(QString(map[4]));
    title->setParent(this);
    title->setDefaultTextColor(Qt::black);
    title->setFont(QFont("Calibri", game->LARGE_FONT / game->zoom()));
    addItem(title);
    title->setZValue(200);

    //название игры
    QGraphicsTextItem * subTitle = new QGraphicsTextItem(QString(QString(map[6])));
    subTitle->setParent(this);
    subTitle->setDefaultTextColor(Qt::black);
    subTitle->setFont(QFont("Calibri", game->MEDIUM_FONT / game->zoom()));
    subTitle->setPos(title->boundingRect().width()/2 - subTitle->boundingRect().width()/2, \
                     title->boundingRect().height());
    addItem(subTitle);
    subTitle->setZValue(200);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(title);

}

void LevelIntro::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        emit win();
    }

    if ((event->key() == Qt::Key_Escape) || (event->key() == Qt::Key_Back))
    {
        game->close();
    }
}

void LevelIntro::mousePressEvent(QMouseEvent *event)
{
    emit win();
}

void LevelIntro::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit win();
}

void LevelIntro::checkRules()
{
}


