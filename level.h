#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QTimer>
#include "cell.h"
#include "dialogBox.h"
#include "player.h"
#include "enemy.h"
#include <QPixmap>

class Level : public QGraphicsScene
{
    Q_OBJECT
public:
    Level(QGraphicsView * parent);
    void init (QString map[]);
    void gameOver (QString comment);
    void levelCompleted (QString message[]);
    QString clues;
    QString startMessage[30];
    QString endMessage[30];
    bool check;
    QPixmap sprites;

    //ввод с клавиатуры
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //некоторые объекты сцены
    unsigned short numberOfEnemies;
    Player * player;
    Enemy * enemy[10];
    QTimer * updateTimer;
    DialogBox * dialog;
    Cell * title;
    Cell * controls;

    //определяем геометрические параметры сцены
    short PLAYER_HEIGHT;
    short PLAYER_WIDTH;
    short ENEMY_HEIGHT;
    short ENEMY_WIDTH;
    
signals:
    void lose();
    void win();

public slots:
    void checkRules();
};

#endif // LEVEL_H
