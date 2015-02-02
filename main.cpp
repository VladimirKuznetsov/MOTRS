#include <QtGui/QApplication>
#include "player.h"
#include <QGraphicsScene>
#include <QGraphicsView>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_WIDTH 60
#define PLAYER_HEIGHT 100
#define GROUND_LEVEL 50

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    //создаём объект игрока
    Player *player = new Player();
    player->setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //создаём сцену и добавляем игрока
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(player);

    //настраиваем параметры отображения
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->setSceneRect(0, 0, 3000, WINDOW_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //устанавливаем игрока на место
    player->setPos(0, 0);
    view->show();

    return a.exec();
}
