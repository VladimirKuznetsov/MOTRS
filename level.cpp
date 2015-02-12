#include "level.h"
#include "game.h"
#include "dialogBox.h"
#include <QGraphicsTextItem>
#include <QDebug>

extern Game * game;

//конструктор
Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{
    //определяем геометрические параметры сцены
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    numberOfEnemies = 0;
    connect(this, SIGNAL(levelCompleted(bool, Level*)), game, SLOT(levelCompleted(bool, Level*)));
}

//загрузка карты из массива строк
void Level::init(QString map[])
{
    //отрисовываем фон
    setBackgroundBrush(QBrush(Qt::gray));

    //создаём таймер, который будет управлять движением
    updateTimer = new QTimer();

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
                player->setZValue(1);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка автомобиля
            if (map[row][column] == 'v')
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
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("Этот гидрант подарил мне отец на день рождения");
                hydrant->interactionDialogue[1] = QString("Это Hydro Jet Super 2000");
                hydrant->interactionDialogue[2] = QString("");
                addItem(hydrant);
            }
        }
    }
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(player);

    //создаём диалоговое поле
    dialog = new DialogBox();
    addItem(dialog);
    connect(player, SIGNAL(interactionStarted(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(interactionEnded(Cell*)), player, SLOT(addActivatedItem(Cell*)));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));

    //запускаем таймер, управляющий движением
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    updateTimer->start(20);
}

//отображаем в случае провала
void Level::gameOver(QString comment)
{
    emit levelCompleted(false,this);
}

//макет проверки правил
void Level::checkRules()
{
}

//отработка нажатий клавиш
void Level::keyPressEvent(QKeyEvent *event)
{
    //режим прокрутки диалога
    if (dialog->isOn == true)
    {
        //прокрутка диалога
        if (event->key() == Qt::Key_Space)
        {
            dialog->nextLine();
        }

    //обычный режим игры
    } else
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
}

//отработка отпускания клавиши
void Level::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}
