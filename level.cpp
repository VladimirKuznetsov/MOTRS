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
    connect(this, SIGNAL(levelCompleted()), game, SLOT(nextLevel()));
    connect(this, SIGNAL(gameOver()), game, SLOT(resetLevel()));
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
            //отрисовка выхода
            if (map[row][column] == 't')
            {
                Cell * target = new Cell(":/img/ground1");
                float scaleFactor = game->CELL_SIZE / target->boundingRect().width();
                target->setScale(scaleFactor);
                target->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                target->isTarget = true;
                target->setOpacity(0);
                addItem(target);
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
            //отрисовка невидимых стен
            if (map[row][column] == 'w')
            {
                Cell * wall = new Cell(":/img/ground1");
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                wall->isSolid = true;
                wall->setOpacity(0);
                addItem(wall);
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

    //загружаем список улик
    clues = map[16];
    clues.remove(' ');

    //определяем размеры сцены
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(player);

    //создаём диалоговое поле
    dialog = new DialogBox();
    addItem(dialog);
    connect(player, SIGNAL(investigating(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(dialogEnded(Cell*)), player, SLOT(addClue(Cell*)));

    //запускаем таймер, управляющий движением
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));
    updateTimer->start(20);

    QString test[10] = {
        "level is about to start",
        "yes it is",
    };
    dialog->setDialog(test);
}

//отображаем в случае провала
void Level::gameOver(QString comment)
{
    updateTimer->stop();
    emit gameOver();
}

void Level::levelCompleted(QString message[])
{
    updateTimer->stop();
    dialog->setDialog(message);
    connect (dialog, SIGNAL(dialogEnded()), this, SIGNAL(levelCompleted()));
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
        switch (event->key())
        {
        //прокрутка диалога
        case (Qt::Key_Space):
            dialog->nextLine();
            break;

        //выход из диалога
        case (Qt::Key_Escape):
            dialog->skip();
            break;

        //в противном случае игнорируем нажатие
        default:
            break;
        }

    //обычный режим игры
    } else
    {
        switch (event->key())
        {
        //выход из игры
        case (Qt::Key_Escape):
            game->close();
            break;

        //передаём управление персонажу
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
