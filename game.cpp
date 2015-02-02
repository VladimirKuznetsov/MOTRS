#include "game.h"
#include "floor.h"
#include <QTimer>
#include <QDebug>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_WIDTH 60
#define PLAYER_HEIGHT 100
#define CELL_SIZE 50

//�������� ����
Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    //������ ������ ������
    player = new Player();
    player->setRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);

    //������ ����� � ��������� ������
    scene = new QGraphicsScene();
    scene->addItem(player);

    //����������� ��������� �����������
    setScene(scene);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //��������� �����
    scene->setSceneRect(0, 0, 3000, WINDOW_HEIGHT);
    for (int i = 0; i < 60; i++) {
        Floor * floor = new Floor();
        floor->setRect(0, 0, CELL_SIZE, CELL_SIZE);
        scene->addItem(floor);
        floor->setPos(i * CELL_SIZE,scene->sceneRect().height() - CELL_SIZE);
    }

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
    qDebug() << "ll";
    ensureVisible(player, WINDOW_WIDTH*3/4, 0);
}
