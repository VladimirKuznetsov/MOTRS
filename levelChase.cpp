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

    if (check == true)
    {
        //������ ���� �������� ������ ���������
        QList <QGraphicsItem *> collisionList = player->collidingItems();
        for (int i = 0; i < collisionList.size(); i++) {
            if (typeid(*collisionList[i]) == (typeid(Enemy))) {
                updateTimer->stop();
                check = false;
                emit win();
            }
        }

        //���������, ���� �������� ������ ������
        if (enemy[0]->x() - player->x() > game->CELL_SIZE * 20) {
            //updateTimer->stop();
            check = false;
            gameOver("���������� ������� ��������.");
        }

        //���������, ���� ��������� ����� �� ������� ������
        if (enemy[0]->x() > sceneRect().width()) {
            //updateTimer->stop();
            check = false;
            gameOver("���������� ������� ��������.");
        }
    }
}
