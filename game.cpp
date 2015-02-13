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
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "w                                                      w",
        "t     H  n      b p  B c          o       b   B   s    t",
        "fffffyfffffgffffffffffffffffffffffffffyffffffffffffffgff",
        "---",
        "scno",
        "---",
        "������� ����� �� ����������� �������� ������ ������ ��������� ������.",
        "��� ������ �������� ��� � ������� �����. �� � ���� ������?",
        "���� ����� �������� ��������� ������ � ������� ������?",
        "�������������, ����! �� ������ ������ ��� ������.",
        "---",
        "����, ��� ������� ������������� ��� ��������� ������...",
        "����� �� ��� ������� ����� ������, �������� ������ ����� � ��������...",
        "�� ����� ��� ���? � ��� ��� ������ ������?",
        "...",
        "����� ����� ������, ���� �����. ��� ������ ������� ������������ �� �������...",
        "---",
        "%",
    };

    QString levelMap1[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "190 180 110",
        "---",
        "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTSSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w  P    k               i         RSSS",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWSSSS",
        "---",
        "ik",
        "---",
        "����� ����������� � ����������� �� �������� ������.",
        "�� �� ������ ������ �� ����� �������� ����...",
        "---",
        "��� ��� �������� ����. ���� ��� �����������.",
        "---",
        "%",
    };

    QString levelMap2[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "110 110 115",
        "---",
        "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTSSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "w                                 RSSS",
        "ta     K               i    P     RSSS",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWSSSS",
        "---",
        "a",
        "---",
        "*���!*",
        "��� ���� ����... ��� ������ �������� � ����� � ����� �����?",
        "---",
        "�������, ��� �� �������...",
        "---",
        "%",
    };

    QString levelMap3[] =
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
        "%",
    };

    QString map[50];

    //��������� ������������ ��� ����� � map[]
    for (int i = 0; i < 50; i++)
    {
        switch (levelNumber)
        {

        case 0:
            if (levelMap0[i] != "%")
            {
                 map[i] = levelMap0[i];
            } else
            {
                i = 50;
            }
            break;

        case 1:
            if (levelMap1[i] != "%")
            {
                map[i] = levelMap1[i];
            } else
            {
                i = 50;
            }
            break;

        case 2:
            if (levelMap2[i] != "%")
            {
                map[i] = levelMap2[i];
            } else
            {
                i = 50;
            }
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

    //����� �� �����
    show();
}

void Game::nextLevel()
{
    qDebug() << "WE GOT A WINNER";
    levelNumber++;
    level->clear();
    //delete level;
    loadLevel();
}

void Game::resetLevel()
{
    qDebug() << "LOOK AT THIS LOOSER";
    level->clear();
    //delete level;
    loadLevel();
}
