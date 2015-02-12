#include "level.h"
#include "game.h"
#include "dialogBox.h"
#include <QGraphicsTextItem>
#include <QDebug>

extern Game * game;

//�����������
Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{
    //���������� �������������� ��������� �����
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    numberOfEnemies = 0;
    connect(this, SIGNAL(levelCompleted(bool, Level*)), game, SLOT(levelCompleted(bool, Level*)));
}

//�������� ����� �� ������� �����
void Level::init(QString map[])
{
    //������������ ���
    setBackgroundBrush(QBrush(Qt::gray));

    //������ ������, ������� ����� ��������� ���������
    updateTimer = new QTimer();

    //�������� ���������� �� ������� �����
    short sceneLength = 0;
    for (int row = 1; row < 16; row++)
    {
        //���������� ����� ����� �� ����� ������� ������
        if (map[row].length() > sceneLength)
        {
            sceneLength = map[row].length();
        }
        //������� ������
        for (int column = 0; column < map[row].length(); column++)
        {
            //��������� ������
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
            //��������� ����������
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
            //��������� ����
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
            //��������� ����
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
            //��������� ����
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
            //��������� ���������
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(":/img/hydrant_a");
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 1) * game->CELL_SIZE);
                hydrant->isSolid = true;

                //��� ����� ������ ������� �������������
                hydrant->addInteraction('h');
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("���� ������� ������� ��� ���� �� ���� ��������");
                hydrant->interactionDialogue[1] = QString("��� Hydro Jet Super 2000");
                hydrant->interactionDialogue[2] = QString("");
                addItem(hydrant);
            }
        }
    }
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //������������� ������ � ��������� ������ �������
    game->setScene(this);
    game->centerOn(player);

    //������ ���������� ����
    dialog = new DialogBox();
    addItem(dialog);
    connect(player, SIGNAL(interactionStarted(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(interactionEnded(Cell*)), player, SLOT(addActivatedItem(Cell*)));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));

    //��������� ������, ����������� ���������
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    updateTimer->start(20);
}

//���������� � ������ �������
void Level::gameOver(QString comment)
{
    emit levelCompleted(false,this);
}

//����� �������� ������
void Level::checkRules()
{
}

//��������� ������� ������
void Level::keyPressEvent(QKeyEvent *event)
{
    //����� ��������� �������
    if (dialog->isOn == true)
    {
        //��������� �������
        if (event->key() == Qt::Key_Space)
        {
            dialog->nextLine();
        }

    //������� ����� ����
    } else
    {
        switch (event->key()) {

        //����� �� ����
        case (Qt::Key_Escape):
            game->close();
            break;

        //���������� ����������
        default:
            player->keyPressEvent(event);
            break;
        }
    }
}

//��������� ���������� �������
void Level::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}
