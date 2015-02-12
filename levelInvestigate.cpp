#include "levelInvestigate.h"
#include "game.h"
#include <typeinfo>
#include <QList>
#include <QDebug>

extern Game * game;

//�����������
LevelInvestigate::LevelInvestigate(QGraphicsView *parent) : Level(parent)
{
}

//�������� ������� ������ � ���������
void LevelInvestigate::checkRules()
{
    //������ ������ �� �����������
    followPlayer();

    //���� ����� ����� �� ������ ������
    QList <QGraphicsItem *> availableItems = player->actionArea->collidingItems();
    for (int i = 0; i < availableItems.size(); i++)
    {
        //������������ ������ ������
        if ((typeid(*availableItems[i]) == typeid(Cell)) && (((Cell*)availableItems[i])->isTarget == true))
        {
            //������� ������ ����
            bool unfoundClues = false;
            for (int i = 0; i < clues.size(); i++)
            {
                if (player->clues.contains(clues[i]) == false) unfoundClues = true;
            }

            //���� ��� ����� �������, ������� ��������
            if (unfoundClues == false)
            {
                levelCompleted(endMessage);
            }
        }
    }
}

//������ ������ �� �������������� ������
void LevelInvestigate::followPlayer()
{
    game->ensureVisible(player, game->WINDOW_WIDTH * 1/5, 0);
}
