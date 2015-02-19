#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QString>
#include <QObject>
#include "level.h"
#include "levelChase.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void loadLevel();
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    Level * level;
    unsigned short levelNumber;
    unsigned short WINDOW_WIDTH;
    unsigned short WINDOW_HEIGHT;
    unsigned short CELL_SIZE;
    unsigned short GRAVITY;
    unsigned short SMALL_FONT;
    unsigned short MEDIUM_FONT;
    unsigned short LARGE_FONT;

    enum Controls{
        mouse = 0,
        keyboard
    }control_mode;

public slots:
    void nextLevel();
    void resetLevel();
    
};

#endif // GAME_H
