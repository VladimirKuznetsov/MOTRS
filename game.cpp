#include "game.h"
#include "cell.h"
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>

//конструктор
Game::Game()
{
    //определяем геометрические параметры сцены
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1000;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    PLAYER_HEIGHT = CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;
}

//отрисовка компонентов игры
void Game::init(QString map[])
{
    //загрузка информации из массива строк
    scene = new QGraphicsScene();
    short sceneLength = 0;
    for (int row = 0; row < 15; row++)
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
            //отрисовка противника
            if (map[row][column] == 'e')
            {
                enemy = new Enemy();
                enemy->setRect(column * CELL_SIZE, row * CELL_SIZE - ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT);
                scene->addItem(enemy);
            }
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell();
                floor->isSolid = true;
                floor->isFloor = true;
                floor->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                floor->setBrush(* new QBrush(Qt::gray));
                scene->addItem(floor);
            }
            //отрисовка гидрантов
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell();
                hydrant->isSolid = true;
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

    centerOn(player);

    //вывод на экран
    show();

    QTimer * ruleCheckTimer = new QTimer();
    connect(ruleCheckTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    ruleCheckTimer->start(5);
}

//отработка нажатий клавиш
void Game::keyPressEvent(QKeyEvent *event)
{
    //прыжок по нажатию на пробел
    if (event->key() == Qt::Key_Up) {
        player->jump();
    }
    //движемся вправо
    if (event->key() == Qt::Key_Right) {
        player->right();
    }
    //движемся влево
    if (event->key() == Qt::Key_Left) {
        player->left();
    }
    //выход по нажатию на Esc
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}

//отработка отпускания клавиши
void Game::keyReleaseEvent(QKeyEvent *event)
{
    //движемся вправо
    if (event->key() == Qt::Key_Right) {
        player->left();
    }
    //движемся влево
    if (event->key() == Qt::Key_Left) {
        player->right();
    }
}

//следим за перемещениями игрока
void Game::followEnemy()
{
    ensureVisible(enemy, WINDOW_WIDTH * 1/5, 0);
}

//проверка условий победы и поражения
void Game::checkRules()
{
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            qDebug() << "WE GOT A WINNER";
        }
    }
}
