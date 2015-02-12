#include "game.h"
#include <math.h>
#include <QDebug>
#include <QVector>
#include <QTextCodec>
#include "levelChase.h"
#include "levelInvestigate.h"

Game::Game()
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

    levelNumber = 0;
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1100;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //����������� ��������� ����������� ����
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::loadLevel()
{
    QString levelMap0[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "140 150 210",
        "---",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "w                                                                             w",
        "t    hhh v    h   h   hh     h   p                   h         h h            w",
        "fffyffffffffffgffffffyfffffffffffyfffffffgffffffffygfffffgfffffffffffffyfffffff",
        "---",
        "h  ",
        "---",
        "����� ����������� � ���� ����� ���������.",
        "---",
        "����, ���� ������ ������� ��� ��������� ������...",
        "�� ��� ��� ������?",
        "...",
        "���? ��� ����� ������?!",
        "�������� ������� ������ �� ������ ������, � ������ �����.",
        "---",
    };

    QString levelMap1[] =
    {
        "LEVEL: CHASE",
        "---",
        "20 20 50",
        "---",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w                                                                              ",
        "w p   hhh v    h   h   hh     h                      h         h h             ",
        "fffyffffffffffgffffffyfffffffffffyfffffffgffffffffygfffffgfffffffffffffyfffffff",
        "---",
        "h  ",
        "---",
        "����� ����������� � ���� ����� ���������.",
        "---",
        "����, ���� ������ ������� ��� ��������� ������...",
        "�� ��� ��� ������?",
        "...",
        "���? ��� ����� ������?!",
        "�������� ������� ������ �� ������ ������, � ������ �����.",
        "---",
    };

    QString map[30];

    //��������� ������������ ��� ����� � map[]
    for (int i = 0; i < 30; i++)
    {
        switch (levelNumber)
        {

        case 0:
            if (levelMap0[i] != QString("")) map[i] = levelMap0[i];
            break;

        case 1:
            if (levelMap1[i] != QString("")) map[i] = levelMap1[i];
            break;

        default:
            break;
        }
    }

    //������ �������: ������
    if (map[0] == QString("LEVEL: CHASE"))
    {
        level = new LevelChase(this);
        level->init(map);

    //������ �������: �������������
    } else if (map[0] == QString("LEVEL: INVESTIGATION"))
    {
        level = new LevelInvestigate(this);
        level->init(map);
    }

/*
    level = new LevelChase(this);
    level->init(levelMap1);
*/
    //����� �� �����
    show();
}

void Game::nextLevel()
{
    qDebug() << "WE GOT A WINNER";
    levelNumber++;
    level->clear();
    delete level;
    loadLevel();
}

void Game::resetLevel()
{
    qDebug() << "LOOK AT THIS LOOSER";
    level->clear();
    delete level;
    loadLevel();
}
