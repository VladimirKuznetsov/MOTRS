#include "levelChase.h"
#include "cell.h"
#include "game.h"
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

//������ �� ������������� ������
void LevelChase::followEnemy()
{
    game->ensureVisible(enemy[0], game->WINDOW_WIDTH * 1/5, 0);
}

//�������� ������� ������ � ���������
void LevelChase::checkRules()
{
    //������ ������ �� �����������
    followEnemy();

    //������ ���� �������� ������ ���������
    QList <QGraphicsItem *> collisionList = player->collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == (typeid(Enemy))) {
            emit levelCompleted();
        }
    }

    //���������, ���� �������� ������ ������
    if (enemy[0]->x() - player->x() > game->CELL_SIZE * 20) {
        gameOver("���������� ������� ��������.");
    }

    //���������, ���� ��������� ����� �� ������� ������
    if (enemy[0]->x() > sceneRect().width()) {
        gameOver("���������� ������� ��������.");
    }
}
