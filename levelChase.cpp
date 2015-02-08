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
    //������ ������, ������� ����� ��������� ���������
    QTimer *updateTimer = new QTimer();

    //�������� ���������� �� ������� �����
    short sceneLength = 0;
    for (int row = 0; row < 15; row++)
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
                player = new Player();
                player->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //��������� ����������
            if (map[row][column] == 'e')
            {
                enemy = new Enemy();
                enemy->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE - ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT);
                addItem(enemy);
                connect(updateTimer, SIGNAL(timeout()), enemy, SLOT(move()));
            }
            //��������� ����
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell(":/img/ground1");
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, row * game->CELL_SIZE);
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
                floor->setPos(column * game->CELL_SIZE, row * game->CELL_SIZE);
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
                floor->setPos(column * game->CELL_SIZE, row * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //��������� ���������
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(":/img/hydrant");
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, row * game->CELL_SIZE);
                hydrant->isSolid = true;
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
    //������ �� ������� �� ������
    if (event->key() == Qt::Key_Up) {
        player->jump();
    }
    //�������� ������
    if (event->key() == Qt::Key_Right) {
        player->right();
    }
    //�������� �����
    if (event->key() == Qt::Key_Left) {
        player->left();
    }
    //����� �� ������� �� Esc
    if (event->key() == Qt::Key_Escape) {
        game->close();
    }
}

//��������� ���������� �������
void LevelChase::keyReleaseEvent(QKeyEvent *event)
{
    //�������� ������
    if (event->key() == Qt::Key_Right) {
        player->left();
    }
    //�������� �����
    if (event->key() == Qt::Key_Left) {
        player->right();
    }
}

//������ �� ������������� ������
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy, game->WINDOW_WIDTH * 1/5, 0);
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

    //��������� ���� �������� ������ ������
    if (enemy->x() - player->x() > game->CELL_SIZE * 10) {
        gameOver(":c");
    }
}
