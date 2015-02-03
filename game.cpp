#include "game.h"
#include "floor.h"
#include <QTimer>
#include <QDebug>

//загрузка игры
Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    //определяем геометрические параметры сцены
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 800;
    PLAYER_HEIGHT = (short)(WINDOW_HEIGHT / 4);
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    CELL_SIZE = WINDOW_HEIGHT / 10;
}

void Game::init()
{
    //создаём объект игрока
    player = new Player();
    player->setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);

    //создаём сцену и добавляем игрока
    scene = new QGraphicsScene();
    scene->addItem(player);

    //настраиваем параметры отображения
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //загружаем сцену
    scene->setSceneRect(0, 0, 3000, WINDOW_HEIGHT);
    for (int i = 0; i < 60; i++) {
        Floor * floor = new Floor();
        floor->setRect(0, 0, CELL_SIZE, CELL_SIZE);
        scene->addItem(floor);
        floor->setPos(i * CELL_SIZE,scene->sceneRect().height() - CELL_SIZE);
    }

    //устанавливаем игрока на место
    player->setPos(0, WINDOW_HEIGHT / 3);

    //вывод на экран
    show();
}

//загрузка сцены из текстового массива
void Game::loadScene(QString map[])
{
}

//отработка нажатий клавиш
void Game::keyPressEvent(QKeyEvent *event)
{
    //прыжок по нажатию на пробел
    if (event->key() == Qt::Key_Space) {
        player->jump();
    }
    //выход по нажатию на Esc
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
}

//следим за перемещениями игрока
void Game::followPlayer()
{
    qDebug() << "ll";
    ensureVisible(player, WINDOW_WIDTH*3/4, 0);
}
