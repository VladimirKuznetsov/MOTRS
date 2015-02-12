#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QString>
#include <QObject>
#include "level.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void loadLevel();

    unsigned short levelNumber;
    unsigned short WINDOW_WIDTH;
    unsigned short WINDOW_HEIGHT;
    unsigned short CELL_SIZE;
    unsigned short GRAVITY;

public slots:
    void nextLevel();
    void resetLevel();
    
};

#endif // GAME_H
