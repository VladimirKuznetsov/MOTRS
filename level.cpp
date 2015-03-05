#include "level.h"
#include "game.h"
#include "dialogBox.h"
#include <QGraphicsTextItem>
#include <QTextCodec>
#include <typeinfo>
#include <QDebug>

extern Game * game;

//конструктор
Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{
    startedMotion = false;

    sprites = QPixmap(":/img/sprites");

    //определяем геометрические параметры сцены
    check = true;
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    numberOfEnemies = 0;
    connect(this, SIGNAL(win()), game, SLOT(nextLevel()));
    connect(this, SIGNAL(lose()), game, SLOT(resetLevel()));
}

//загрузка карты из массива строк
void Level::init(QString map[])
{
    //отрисовываем фон
    QStringList colors = map[2].split(' ');
    setBackgroundBrush(QBrush(QColor(colors[0].toInt(), colors[1].toInt(), colors[2].toInt())));

    //создаём таймер, который будет управлять движением
    updateTimer = new QTimer(this);

    //загрузка информации из массива строк
    short sceneLength = 0;
    for (int row = 4; row < 19; row++)
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
                player = new Player(sprites.copy(0,0,700,300));
                float scaleFactor = PLAYER_HEIGHT / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - PLAYER_HEIGHT);
                player->setZValue(10);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка игрока посреди ночи
            if (map[row][column] == 'P')
            {
                player = new Player(sprites.copy(0,760,700,300));
                float scaleFactor = PLAYER_HEIGHT / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - PLAYER_HEIGHT);
                player->setZValue(10);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка автомобиля
            if (map[row][column] == 'v')
            {
                enemy[numberOfEnemies] = new Enemy(sprites.copy(0,270,388,118), this);
                float scaleFactor = ENEMY_HEIGHT / enemy[numberOfEnemies]->boundingRect().height();
                enemy[numberOfEnemies]->setScale(scaleFactor);
                enemy[numberOfEnemies]->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - ENEMY_HEIGHT);
                addItem(enemy[numberOfEnemies]);
                enemy[numberOfEnemies]->setParent(this);
                connect(updateTimer, SIGNAL(timeout()), enemy[numberOfEnemies], SLOT(move()));

                numberOfEnemies++;
            }
            //отрисовка выхода
            if (map[row][column] == 't')
            {
                Cell * target = new Cell(this);
                target->setPicInactive(sprites.copy(210,390,30,30));
                target->setCellInactive();
                float scaleFactor = game->CELL_SIZE / target->boundingRect().width();
                target->setScale(scaleFactor);
                target->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - target->boundingRect().height()*scaleFactor);
                target->isTarget = true;
                target->setOpacity(0);
                addItem(target);
            }
            //отрисовка пола
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell(this);
                floor->setPicInactive(sprites.copy(0,390,30,30));
                floor->setCellInactive();
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - floor->boundingRect().height()*scaleFactor);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка пола
            if (map[row][column] == 'g')
            {
                Cell * floor = new Cell(this);
                floor->setPicInactive(sprites.copy(30,390,30,30));
                floor->setCellInactive();
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - floor->boundingRect().height()*scaleFactor);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка пола
            if (map[row][column] == 'y')
            {
                Cell * floor = new Cell(this);
                floor->setPicInactive(sprites.copy(60,390,30,30));
                floor->setCellInactive();
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - floor->boundingRect().height()*scaleFactor);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка деревянного пола
            if (map[row][column] == 'W')
            {
                Cell * floor = new Cell(this);
                floor->setPicInactive(sprites.copy(180,390,30,30));
                floor->setCellInactive();
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - floor->boundingRect().height()*scaleFactor);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка деревянных cтен
            if (map[row][column] == 'R')
            {
                Cell * wall = new Cell(this);
                wall->setPicInactive(sprites.copy(210,390,30,30));
                wall->setCellInactive();
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - wall->boundingRect().height()*scaleFactor);
                wall->isSolid = true;
                addItem(wall);
            }
            //отрисовка деревянного потолка
            if (map[row][column] == 'T')
            {
                Cell * ceiling = new Cell(this);
                ceiling->setPicInactive(sprites.copy(240,390,30,30));
                ceiling->setCellInactive();
                float scaleFactor = game->CELL_SIZE / ceiling->boundingRect().width();
                ceiling->setScale(scaleFactor);
                ceiling->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - ceiling->boundingRect().height()*scaleFactor);
                ceiling->isSolid = true;
                addItem(ceiling);
            }
            //отрисовка цельного дерева
            if (map[row][column] == 'S')
            {
                Cell * solid = new Cell(this);
                solid->setPicInactive(sprites.copy(0,420,30,30));
                solid->setCellInactive();
                float scaleFactor = game->CELL_SIZE / solid->boundingRect().width();
                solid->setScale(scaleFactor);
                solid->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - solid->boundingRect().height()*scaleFactor);
                solid->isSolid = true;
                addItem(solid);
            }
            //отрисовка бетонного пола
            if (map[row][column] == 'C')
            {
                Cell * floor = new Cell(this);
                floor->setPicInactive(sprites.copy(90,390,30,30));
                floor->setCellInactive();
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - floor->boundingRect().height()*scaleFactor);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка бетонных cтен
            if (map[row][column] == 'r')
            {
                Cell * wall = new Cell(this);
                wall->setPicInactive(sprites.copy(120,390,30,30));
                wall->setCellInactive();
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - wall->boundingRect().height()*scaleFactor);
                wall->isSolid = true;
                addItem(wall);
            }
            //отрисовка бетонного потолка
            if (map[row][column] == 'U')
            {
                Cell * ceiling = new Cell(this);
                ceiling->setPicInactive(sprites.copy(150,390,30,30));
                ceiling->setCellInactive();
                float scaleFactor = game->CELL_SIZE / ceiling->boundingRect().width();
                ceiling->setScale(scaleFactor);
                ceiling->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - ceiling->boundingRect().height()*scaleFactor);
                ceiling->isSolid = true;
                addItem(ceiling);
            }
            //отрисовка цельного бетона
            if (map[row][column] == 'F')
            {
                Cell * solid = new Cell(this);
                solid->setPicInactive(sprites.copy(30,420,30,30));
                solid->setCellInactive();
                float scaleFactor = game->CELL_SIZE / solid->boundingRect().width();
                solid->setScale(scaleFactor);
                solid->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - solid->boundingRect().height()*scaleFactor);
                solid->isSolid = true;
                addItem(solid);
            }
            //отрисовка невидимых стен
            if (map[row][column] == 'w')
            {
                Cell * wall = new Cell(this);
                wall->setPicInactive(sprites.copy(210,390,30,30));
                wall->setCellInactive();
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - wall->boundingRect().height()*scaleFactor);
                wall->isSolid = true;
                wall->setOpacity(0);
                addItem(wall);
            }
            //отрисовка гидрантов - препятствий
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(this);
                hydrant->setPicInactive(sprites.copy(0,450,30,30));
                hydrant->setCellInactive();
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - hydrant->boundingRect().height()*scaleFactor);
                hydrant->isSolid = true;
                addItem(hydrant);
            }
            //отрисовка фоновых гидрантов
            if (map[row][column] == 'H')
            {
                Cell * hydrant = new Cell(this);
                hydrant->setPicActive(sprites.copy(0,450,30,30));
                hydrant->setPicActivated(sprites.copy(30,450,30,30));
                hydrant->setCellActive();
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - hydrant->boundingRect().height()*scaleFactor);
                hydrant->addInteraction('h');
                hydrant->interactionDialogue[0] = QString(tr("I'd better not touch enything..."));
                addItem(hydrant);
            }
            //отрисовка автомобиля без тюленя
            if (map[row][column] == 'n')
            {
                Cell * van_ns = new Cell(this);
                van_ns->setPicActive(sprites.copy(388,270,194,118));
                van_ns->setPicActivated(sprites.copy(388,270,194,118));
                van_ns->setCellActive();
                qreal scaleFactor = game->CELL_SIZE * 4 / van_ns->boundingRect().height();
                van_ns->setScale(scaleFactor);
                van_ns->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * van_ns->boundingRect().height());
                van_ns->addInteraction('n');
                van_ns->interactionDialogue[0] = QString(tr("This car belongs to the zoo."));
                addItem(van_ns);
                van_ns->setZValue(2);
            }
            //отрисовка фоновых кустов
            if (map[row][column] == 'b')
            {
                Cell * bush = new Cell(this);
                bush->setPicInactive(sprites.copy(0,480,103,106));
                bush->setCellInactive();
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //отрисовка фоновых кустов
            if (map[row][column] == 'B')
            {
                Cell * bush = new Cell(this);
                bush->setPicInactive(sprites.copy(103,480,167,106));
                bush->setCellInactive();
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //отрисовка мячика
            if (map[row][column] == 's')
            {
                Cell * ball = new Cell(this);
                ball->setPicActive(sprites.copy(60,450,30,30));
                ball->setPicActivated(sprites.copy(60,450,30,30));
                ball->setCellActive();
                float scaleFactor = game->CELL_SIZE * 1.2/ ball->boundingRect().height();
                ball->setScale(scaleFactor);
                ball->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * ball->boundingRect().height());
                ball->addInteraction('s');
                ball->interactionDialogue[0] = QString(tr("This is the ball for the seal show. Now it's getting creepy..."));
                addItem(ball);
                ball->setZValue(-2);
            }
            //отрисовка клетки для тюленя
            if (map[row][column] == 'c')
            {
                Cell * cell = new Cell(this);
                cell->setPicActive(sprites.copy(270,480,171,106));
                cell->setPicActivated(sprites.copy(270,480,171,106));
                cell->setCellActive();
                float scaleFactor = (float)game->CELL_SIZE * 5 / cell->boundingRect().height();
                cell->setScale(scaleFactor);
                cell->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * cell->boundingRect().height());
                cell->addInteraction('c');
                qDebug() << QString::number(cell->boundingRect().height());
                cell->interactionDialogue[0] = QString(tr("This door seems to be the only way out of the cage..."));
                cell->interactionDialogue[1] = QString(tr("...what if somebody helped our seal to run away?"));
                addItem(cell);
            }
            //отрисовка г-на Огурцова
            if (map[row][column] == 'o')
            {
                Cell * mr = new Cell(this);
                mr->setPicActive(sprites.copy(110,0,60,80));
                mr->setPicActivated(sprites.copy(110,0,60,80));
                mr->setCellActive();
                float scaleFactor = (float)PLAYER_HEIGHT / mr->boundingRect().height();
                mr->setScale(scaleFactor);
                mr->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * mr->boundingRect().height());
                mr->addInteraction('o');
                mr->interactionDialogue[0] = QString(tr("–Mr Ogurtsov I suppose? My name is detective Daria Vinokurova."));
                mr->interactionDialogue[1] = QString(tr("Did you call the police?"));
                mr->interactionDialogue[2] = QString(tr("–Yes. This night a ribbon seal disappeared from its cage."));
                mr->interactionDialogue[3] = QString(tr("Please find him, detective!"));
                mr->interactionDialogue[4] = QString(tr("–We'll handle this situation, mr Ogurtsov. Who had the keys to the cage?"));
                mr->interactionDialogue[5] = QString(tr("–Our watchman had."));
                mr->interactionDialogue[6] = QString(tr("–Can I speak to him?"));
                mr->interactionDialogue[7] = QString(tr("–Unfortunately no. He didn't come to work today."));
                mr->interactionDialogue[8] = QString(tr("–That's interesting..."));
                addItem(mr);
            }
            //отрисовка молчаливого г-на Огурцова
            if (map[row][column] == 'O')
            {
                Cell * mr = new Cell(this);
                mr->setPicInactive(sprites.copy(110,0,60,80));
                mr->setCellInactive();
                float scaleFactor = (float)PLAYER_HEIGHT / mr->boundingRect().height();
                mr->setScale(scaleFactor);
                mr->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * mr->boundingRect().height());
                addItem(mr);
            }
            //отрисовка кухни
            if (map[row][column] == 'k')
            {
                Cell * kitchen = new Cell(this);
                kitchen->setPicActive(sprites.copy(0,586,160,106));
                kitchen->setPicActivated(sprites.copy(160,586,160,106));
                kitchen->setCellActive();
                float scaleFactor = game->CELL_SIZE * 3 / kitchen->boundingRect().height();
                kitchen->setScale(scaleFactor);
                kitchen->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * kitchen->boundingRect().height());
                kitchen->addInteraction('k');
                kitchen->interactionDialogue[0] = QString(tr("That's a damn fine cup of coffee..."));
                kitchen->interactionDialogue[1] = QString(tr("Now I need a good sleep."));
                addItem(kitchen);
            }
            //отрисовка ночной кухни
            if (map[row][column] == 'K')
            {
                Cell * kitchen = new Cell(this);
                kitchen->setPicInactive(sprites.copy(320,586,160,106));
                kitchen->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 3 / kitchen->boundingRect().height();
                kitchen->setScale(scaleFactor);
                kitchen->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * kitchen->boundingRect().height());
                addItem(kitchen);
            }
            //отрисовка кровати
            if (map[row][column] == 'i')
            {
                Cell * bed = new Cell(this);
                bed->setPicActive(sprites.copy(0,692,115,57));
                bed->setPicActivated(sprites.copy(0,692,115,57));
                bed->setCellActive();
                float scaleFactor = game->CELL_SIZE * 3 / bed->boundingRect().width();
                bed->setScale(scaleFactor);
                bed->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bed->boundingRect().height());
                bed->isTarget = true;
                addItem(bed);
            }
            //отрисовка кровати
            if (map[row][column] == 'I')
            {
                Cell * bed = new Cell(this);
                bed->setPicInactive(sprites.copy(115,692,115,57));
                bed->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 3 / bed->boundingRect().width();
                bed->setScale(scaleFactor);
                bed->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bed->boundingRect().height());
                addItem(bed);
            }
            //отрисовка письма
            if (map[row][column] == 'a')
            {
                Cell * letter = new Cell(this);
                letter->setPicActive(sprites.copy(230,692,16,10));
                letter->setPicActivated(sprites.copy(0,0,1,1));
                letter->setCellActive();
                float scaleFactor = game->CELL_SIZE *0.3 / letter->boundingRect().height();
                letter->setScale(scaleFactor);
                letter->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * letter->boundingRect().height());
                letter->addInteraction('a');
                letter->interactionDialogue[0] = QString(tr("Anonymous letter?"));
                letter->interactionDialogue[1] = QString(tr("«Daria, I'm sorry that I can't meet you personally...»"));
                letter->interactionDialogue[2] = QString(tr("...I hate when somebody calls me Daria..."));
                letter->interactionDialogue[3] = QString(tr("«...but I have to stay anonymous for the sefety of both of us."));
                letter->interactionDialogue[4] = QString(tr("I have some information about the case you're  currently working on."));
                letter->interactionDialogue[5] = QString(tr("The seal is being kept in the old warehouse of the metalworks factory."));
                letter->interactionDialogue[6] = QString(tr("Somebody has to save this poor animal.»"));
                addItem(letter);
            }
            //отрисовка ящиков
            if (map[row][column] == 'q')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(90,450,30,30));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 2 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'Q')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(580,390,120,120));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'J')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(580,510,120,120));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'j')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(120,450,30,30));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 2 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'Z')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(580,630,120,120));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'z')
            {
                Cell * box = new Cell(this);
                box->setPicInactive(sprites.copy(150,450,30,30));
                box->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 2 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка документов
            if (map[row][column] == 'd')
            {
                Cell * docs = new Cell(this);
                docs->setPicActive(sprites.copy(230,705,23,5));
                docs->setPicActivated(sprites.copy(0,0,1,1));
                docs->setCellActive();
                float scaleFactor = game->CELL_SIZE / docs->boundingRect().width();
                docs->setScale(scaleFactor);
                docs->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*docs->boundingRect().height());
                docs->addInteraction('d');
                docs->interactionDialogue[0] = QString(tr("Insurance papers..."));
                docs->interactionDialogue[1] = QString(tr("Seems like the zoo will get a huge sum of money if the seal doesn't show up."));
                docs->interactionDialogue[2] = QString(tr("I bet mr Ogurtsov knows it."));
                docs->interactionDialogue[3] = QString(tr("But how did those papers get here?.."));
                addItem(docs);
            }
            //отрисовка сигарет
            if (map[row][column] == 'L')
            {
                Cell * cig = new Cell(this);
                cig->setPicActive(sprites.copy(230,710,23,1));
                cig->setPicActivated(sprites.copy(230,710,23,1));
                cig->setCellActive();
                float scaleFactor = game->CELL_SIZE / cig->boundingRect().width();
                cig->setScale(scaleFactor);
                cig->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*cig->boundingRect().height());
                cig->addInteraction('L');
                cig->interactionDialogue[0] = QString(tr("Cigarette butts. Fresh."));
                addItem(cig);
            }
            //отрисовка миски
            if (map[row][column] == 'V')
            {
                Cell * food = new Cell(":/img/food", 0, this);
                food->setPicActive(sprites.copy(230,715,20,14));
                food->setPicActivated(sprites.copy(230,715,20,14));
                food->setCellActive();
                float scaleFactor = game->CELL_SIZE * 0.6 / food->boundingRect().width();
                food->setScale(scaleFactor);
                food->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*food->boundingRect().height());
                food->addInteraction('V');
                food->interactionDialogue[0] = QString(tr("A bowl of fish."));
                food->interactionDialogue[1] = QString(tr("Does someone keep a cat here?"));
                addItem(food);
            }
            //отрисовка титров
            if (map[row][column] == 'E')
            {
                Cell * end = new Cell(this);
                end->setPicInactive(sprites.copy(260,705,151,41));
                end->setCellInactive();
                float scaleFactor = game->CELL_SIZE * 7 / end->boundingRect().width();
                end->setScale(scaleFactor);
                end->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * end->boundingRect().height());
                addItem(end);
            }
        }
    }

    //загружаем список улик
    clues = map[20];
    clues.remove(' ');

    //загружаем начальное и финальное сообщение уровня
    int i;
    for (i = 22; i < 52; i++)
    {
        if (map[i] == QString("---")) break;
        startMessage[i - 22] = map[i];
    }
    startMessage[i - 22] = "";

    i++;
    int j;
    for (j = i; j < i + 30; j++)
    {
        if (map[j] == QString("---")) break;
        endMessage[j - i] = map[j];
    }
    endMessage[j - i] = "";

    zoom = map[j + 1].toDouble();
    game->scale(zoom, zoom);

    //определяем размеры сцены
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(player->x(), player->y());
    game->ensureVisible(player, game->width() / 3, game->height() / 10);

    //создаём диалоговое поле
    dialog = new DialogBox();
    addItem(dialog);
    dialog->setParent(this);
    connect(player, SIGNAL(investigating(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(ended(Cell*)), player, SLOT(addClue(Cell*)));

    //запускаем таймер, управляющий движением
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));
    updateTimer->start(30);

    //загрузка начального диалога
    dialog->setDialog(startMessage);
}

//отображаем в случае провала
void Level::gameOver(QString comment)
{
    updateTimer->stop();
    emit lose();
}

//отрабатываем клик мышкой
void Level::levelCompleted(QString message[])
{
    updateTimer->stop();
    connect (dialog, SIGNAL(ended()), this, SIGNAL(win()));
    dialog->setDialog(message);
}

//обработка нажатия мыши
void Level::mousePressEvent(QMouseEvent * event)
{
    //прокрутка диалога
    if (dialog->isOn == true)
    {
        dialog->nextLine();

    //движение в сторону клика
    } else
    {
        //эта переменная нужна, чтобы персонаж не начинал движение
        //при отпускании нажатия на последней строчки диалога
        startedMotion = true;

        //сбрасываем предыдущую цель движения
        player->targetX = -1;
        player->targetCell->shortSymbol = ' ';

        //определяем координаты клика в системе координат сцены
        int clickX = game->mapToScene(event->x(), event->y()).rx();

        QKeyEvent * keyEvent = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Right, 0, "", false, 1);
        player->keyReleaseEvent(keyEvent);
        keyEvent = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Shift, 0, "", false, 1);
        player->keyReleaseEvent(keyEvent);
        keyEvent = new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Left, 0, "", false, 1);
        player->keyReleaseEvent(keyEvent);

        //движемся в заданном направлении
        if (player->x() < clickX)
        {
            keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Right, 0, "", false, 1);
            player->keyPressEvent(keyEvent);
        } else
        {
            keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Left, 0, "", false, 1);
            player->keyPressEvent(keyEvent);
        }
    }
}

//отрабатываем двойной клик
void Level::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (dialog->isOn == true)
    {
        dialog->nextLine();
    } else
    {
        mousePressEvent(event);
        QKeyEvent * keyEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Shift, 0, "", false, 1);
        player->keyPressEvent(keyEvent);
    }
}

void Level::mouseReleaseEvent(QMouseEvent *event)
{

    if (startedMotion == true)
    {
        //задаём движение в сторону той точки, где прекратилось нажатие
        mousePressEvent(event);

        //задаём цель движения в координатах сцены
        player->targetX = game->mapToScene(event->x(), event->y()).rx();

        //проверяем объекты под курсором (исключаем игрока из проверки)
        player->setVisible(false);
        QGraphicsItem * clickedItem = itemAt(game->mapToScene(event->x(), event->y()), QTransform());
        if (clickedItem)
        {
            if (typeid(*clickedItem) == typeid(Cell))
            {
                if (((Cell*)clickedItem)->isInteractive == true)
                {
                    player->targetCell = dynamic_cast<Cell *>(clickedItem);
                }
            }
        }
        player->setVisible(true);
    }
    startedMotion = false;
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

    if (event->key() == Qt::Key_Back)
    {
        QKeyEvent *virtualEvent = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Escape, 0, "", false, 0);
        keyPressEvent(virtualEvent);
        return;
    }
}

//отработка отпускания клавиши
void Level::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}
