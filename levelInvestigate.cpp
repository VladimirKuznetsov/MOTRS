#include "levelInvestigate.h"
#include "game.h"
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

    //������� ������ ����
    bool unfoundClues = false;
    for (int i = 0; i < clues.size(); i++)
    {
        if (player->clues.contains(clues[i]) == false) unfoundClues = true;
    }

    //���� ��� ����� �������, ������� ��������
    if (unfoundClues == false)
    {
        QString exitingMessage[10] =
        {
            "����, ���� ������ ������� ��� ��������� ������...",
            "�� ��� ��� ������?",
            "...",
            "���? ��� ����� ������?!",
            "�������� ������� ������ �� ������ ������, � ������ �����.",
        };
        levelCompleted(exitingMessage);
    }
}

//������ ������ �� �������������� ������
void LevelInvestigate::followPlayer()
{
    game->ensureVisible(player, game->WINDOW_WIDTH * 1/5, 0);
}
