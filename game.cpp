#include "game.h"
#include "cell.h"
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>

//�����������
Game::Game()
{
    //���������� �������������� ��������� �����
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1000;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    PLAYER_HEIGHT = CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;
}

//��������� ����������� ����
void Game::init(QString map[])
{
    //�������� ���������� �� ������� �����
    scene = new QGraphicsScene();
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
                player->setRect(column * CELL_SIZE, row * CELL_SIZE - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
                scene->addItem(player);
            }
            //��������� ����������
            if (map[row][column] == 'e')
            {
                enemy = new Enemy();
                enemy->setRect(column * CELL_SIZE, row * CELL_SIZE - ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT);
                scene->addItem(enemy);
            }
            //��������� ����
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell();
                floor->isSolid = true;
                floor->isFloor = true;
                floor->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                floor->setBrush(* new QBrush(Qt::gray));
                scene->addItem(floor);
            }
            //��������� ���������
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
    //����������� ��������� �����������
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    centerOn(player);

    //����� �� �����
    show();

    QTimer * ruleCheckTimer = new QTimer();
    connect(ruleCheckTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    ruleCheckTimer->start(5);
}

//��������� ������� ������
void Game::keyPressEvent(QKeyEvent *event)
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
        close();
    }
}

//��������� ���������� �������
void Game::keyReleaseEvent(QKeyEvent *event)
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
void Game::followEnemy()
{
    ensureVisible(enemy, WINDOW_WIDTH * 1/5, 0);
}

//�������� ������� ������ � ���������
void Game::checkRules()
{
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            qDebug() << "WE GOT A WINNER";
        }
    }
}
