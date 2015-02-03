#include "game.h"
#include "floor.h"
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
    //создаём объект игрока
    player = new Player();
    player->setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);

    //создаём сцену и добавляем игрока
    scene = new QGraphicsScene();
    scene->addItem(player);

    //загрузка информации из массива map
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
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Floor * floor = new Floor();
                floor->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                scene->addItem(floor);
            }
        }
    }
    scene->setSceneRect(0, 0, sceneLength * CELL_SIZE, WINDOW_HEIGHT);

    //настраиваем параметры отображения
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //устанавливаем игрока на место
    player->setPos(0, WINDOW_HEIGHT / 3);

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
