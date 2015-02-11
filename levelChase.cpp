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

//�����������
LevelChase::LevelChase(QGraphicsView * parent) : Level(parent)
{
}

//��������� ����������� ����
void LevelChase::init(QString map[])
{
    setBackgroundBrush(QBrush(Qt::gray));

    //������ ������, ������� ����� ��������� ���������
    QTimer *updateTimer = new QTimer();

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
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //��������� ����������
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


                addItem(hydrant);
            }
        }
    }
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //������������� ������ � ��������� ������ �������
    game->setScene(this);
    game->centerOn(player);

    //��������� ������, ����������� ���������
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(followEnemy()));
    updateTimer->start(20);
}

//��������� ������� ������
void LevelChase::keyPressEvent(QKeyEvent *event)
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

//��������� ���������� �������
void LevelChase::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}

//������ �� ������������� ������
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy[0], game->WINDOW_WIDTH * 1/5, 0);
}

//�������� ������� ������ � ���������
void LevelChase::checkRules()
{
    //������ ���� �������� ������ ���������
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            emit levelCompleted(true, this);
        }
    }

    //������������ ������!
    //��������� ���� �������� ������ ������
    if (enemy[0]->x() - player->x() > game->CELL_SIZE * 20) { //10
        gameOver(":c");
    }
}
