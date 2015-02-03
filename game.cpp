#include "game.h"
#include "solid.h"
#include <QTimer>
#include <QDebug>
#include <QString>

//конструктор
Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    //определяем геометрические параметры сцены
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 800;
    CELL_SIZE = WINDOW_HEIGHT / 10;
    PLAYER_HEIGHT = CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
}

//отрисовка компонентов игры
void Game::init(QString map[])
{
    //загрузка информации из массива строк
    scene = new QGraphicsScene();
    short sceneLength = 0;
    for (int row = 0; row < 10; row++)
    {
        //определяем длину сцены по самой длинной строке
        if (map[row].length() > sceneLength)
        {
            sceneLength = map[row].length();
        }
        //парсинг строки
        for (int column = 0; column < map[row].length(); column++)
        {
            //отрисовка игрока
            if (map[row][column] == 'p')
            {
                player = new Player();
                player->setRect(column * CELL_SIZE, row * CELL_SIZE - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                scene->addItem(player);
            }
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Solid * floor = new Solid();
                floor->kind = Solid::KindFloor;
                floor->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                floor->setBrush(* new QBrush(Qt::gray));
                scene->addItem(floor);
            }
            //отрисовка гидрантов
            if (map[row][column] == 'h')
            {
                Solid * hydrant = new Solid();
                hydrant->kind = Solid::KindObstacle;
                hydrant->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                hydrant->setBrush(* new QBrush(Qt::red));
                scene->addItem(hydrant);
            }
        }
    }
    scene->setSceneRect(0, 0, sceneLength * CELL_SIZE, WINDOW_HEIGHT);

    //настраиваем параметры отображения
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //вывод на экран
    show();
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
    ensureVisible(player, WINDOW_WIDTH*3/4, 0);
}
