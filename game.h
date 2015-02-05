#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QString>
#include <QObject>

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

public slots:
    void levelCompleted(bool result);
    
};

#endif // GAME_H
