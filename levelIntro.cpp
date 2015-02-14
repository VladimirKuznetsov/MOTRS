#include "levelIntro.h"
#include <QGraphicsTextItem>
#include "game.h"

extern Game * game;

LevelIntro::LevelIntro(QGraphicsView *parent) : Level(parent)
{
    step = 0;
}

void LevelIntro::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        step++;
        switch(step) {
        case 1:
            controls->setZValue(101);
            title->setZValue(100);
            break;
        case 2:
            emit win();
            break;
        }
    }
}

void LevelIntro::checkRules()
{
}


