#include "levelChase.h"
#include "cell.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>
#include <QGraphicsItem>
#include <float.h>

extern Game * game;

//конструктор
LevelChase::LevelChase(QGraphicsView * parent) : Level(parent)
{
}

//отрисовка компонентов игры
void LevelChase::init(QString map[])
{
    setBackgroundBrush(QBrush(Qt::gray));

    //создаём таймер, который будет управлять движением
    QTimer *updateTimer = new QTimer();

    //загрузка информации из массива строк
    short sceneLength = 0;
    for (int row = 1; row < 16; row++)
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
                player = new Player(":/img/dasha");
                float scaleFactor = PLAYER_HEIGHT / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE - PLAYER_HEIGHT);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка противника
            if (map[row][column] == 'e')
            {
                enemy[numberOfEnemies] = new Enemy(":/img/van/");
                float scaleFactor = ENEMY_HEIGHT / enemy[numberOfEnemies]->boundingRect().height();
                enemy[numberOfEnemies]->setScale(scaleFactor);
                enemy[numberOfEnemies]->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE - ENEMY_HEIGHT);
                addItem(enemy[numberOfEnemies]);
                connect(updateTimer, SIGNAL(timeout()), enemy[numberOfEnemies], SLOT(move()));

                numberOfEnemies++;
            }
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell(":/img/ground1");
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка пола
            if (map[row][column] == 'g')
            {
                Cell * floor = new Cell(":/img/ground2");
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка пола
            if (map[row][column] == 'y')
            {
                Cell * floor = new Cell(":/img/ground3");
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка гидрантов
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(":/img/hydrant_a");
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                hydrant->isSolid = true;

                //ДЛЯ ТЕСТА ДЕЛАЕМ ГИДРАНТ ИНТЕРАКТИВНЫМ
                hydrant->addInteraction('h');


                addItem(hydrant);
            }
        }
    }
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(player);

    //запускаем таймер, управляющий движением
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(followEnemy()));
    updateTimer->start(20);
}

//отработка нажатий клавиш
void LevelChase::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

    //выход из игры
    case (Qt::Key_Escape):
        game->close();
        break;

    //управление персонажем
    default:
        player->keyPressEvent(event);
        break;
    }
}

//отработка отпускания клавиши
void LevelChase::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}

//следим за перемещениями игрока
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy[0], game->WINDOW_WIDTH * 1/5, 0);
}

//проверка условий победы и поражения
void LevelChase::checkRules()
{
    //победа если персонаж догнал соперника
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            emit levelCompleted(true, this);
        }
    }

    //перерисовать тюленя!
    //поражение если персонаж сильно отстал
    if (enemy[0]->x() - player->x() > game->CELL_SIZE * 20) { //10
        gameOver(":c");
    }
}
