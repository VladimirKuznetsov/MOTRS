#include "game.h"
#include "floor.h"
#include <QTimer>
#include <QDebug>
#include <QString>

//�����������
Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    //���������� �������������� ��������� �����
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 800;
    CELL_SIZE = WINDOW_HEIGHT / 10;
    PLAYER_HEIGHT = CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
}

//��������� ����������� ����
void Game::init(QString map[])
{
    //������ ������ ������
    player = new Player();
    player->setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);

    //������ ����� � ��������� ������
    scene = new QGraphicsScene();
    scene->addItem(player);

    //�������� ���������� �� ������� map
    short sceneLength = 0;
    for (int row = 0; row < 10; row++)
    {
        //���������� ����� ����� �� ����� ������� ������
        if (map[row].length() > sceneLength)
        {
            sceneLength = map[row].length();
        }
        //������� ������
        for (int column = 0; column < map[row].length(); column++)
        {
            //��������� ����
            if (map[row][column] == 'f')
            {
                Floor * floor = new Floor();
                floor->setRect(column * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                scene->addItem(floor);
            }
        }
    }
    scene->setSceneRect(0, 0, sceneLength * CELL_SIZE, WINDOW_HEIGHT);

    //����������� ��������� �����������
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //������������� ������ �� �����
    player->setPos(0, WINDOW_HEIGHT / 3);

    //����� �� �����
    show();
}

//��������� ������� ������
void Game::keyPressEvent(QKeyEvent *event)
{
    //������ �� ������� �� ������
    if (event->key() == Qt::Key_Space) {
        player->jump();
    }
    //����� �� ������� �� Esc
    if (event->key() == Qt::Key_Escape) {
        this->close();
    }
}

//������ �� ������������� ������
void Game::followPlayer()
{
    ensureVisible(player, WINDOW_WIDTH*3/4, 0);
}
