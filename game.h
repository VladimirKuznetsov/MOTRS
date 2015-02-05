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
    void loadLevel(int levelNumber);

    short WINDOW_WIDTH;
    short WINDOW_HEIGHT;
    short CELL_SIZE;
    short GRAVITY;

public slots:
    void levelCompleted(bool result,Level * level);
    
};

#endif // GAME_H
