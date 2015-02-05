#include "levelChase.h"
#include "cell.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>

extern Game * game;

//конструктор
LevelChase::LevelChase()
{
    //определяем геометрические параметры сцены
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;
}

//отрисовка компонентов игры
void LevelChase::init(QString map[])
{
    //создаём таймер, который будет управлять движением
    QTimer *updateTimer = new QTimer();

    //загрузка информации из массива строк
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
                player->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка противника
            if (map[row][column] == 'e')
            {
                enemy = new Enemy();
                enemy->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE - ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT);
                addItem(enemy);
                connect(updateTimer, SIGNAL(timeout()), enemy, SLOT(move()));
            }
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell();
                floor->isSolid = true;
                floor->isFloor = true;
                floor->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE, game->CELL_SIZE, game->CELL_SIZE);
                floor->setBrush(* new QBrush(Qt::gray));
                addItem(floor);
            }
            //отрисовка гидрантов
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell();
                hydrant->isSolid = true;
                hydrant->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE, game->CELL_SIZE, game->CELL_SIZE);
                hydrant->setBrush(* new QBrush(Qt::red));
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
    updateTimer->start(25);
}

//отработка нажатий клавиш
void LevelChase::keyPressEvent(QKeyEvent *event)
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
        game->close();
    }
}

//отработка отпускания клавиши
void LevelChase::keyReleaseEvent(QKeyEvent *event)
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
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy, game->WINDOW_WIDTH * 1/5, 0);
}

//проверка условий победы и поражения
void LevelChase::checkRules()
{
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            qDebug() << "WE GOT A WINNER";
        }
    }
}
