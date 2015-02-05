#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QString>

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
    QString levelMap[];
    
signals:
    
public slots:
    
};

#endif // GAME_H
