#include "levelChase.h"
#include "cell.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QList>
#include <typeinfo>

extern Game * game;

//�����������
LevelChase::LevelChase()
{
    //���������� �������������� ��������� �����
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;
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
                Cell * floor = new Cell();
                floor->isSolid = true;
                floor->isFloor = true;
                floor->setRect(column * game->CELL_SIZE, row * game->CELL_SIZE, game->CELL_SIZE, game->CELL_SIZE);
                floor->setBrush(* new QBrush(Qt::gray));
                addItem(floor);
            }
            //��������� ���������
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

    //������������� ������ � ��������� ������ �������
    game->setScene(this);
    game->centerOn(player);

    //��������� ������, ����������� ���������
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(followEnemy()));
    updateTimer->start(25);
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
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            qDebug() << "WE GOT A WINNER";
        }
    }
}
