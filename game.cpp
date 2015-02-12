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
    WINDOW_HEIGHT = 700;
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
/*
    QString map[27];

    //��������� ������������ ��� ����� � map[]
    for (int i = 0; i < 27; i++)
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
        LevelChase * level = new LevelChase(this);
        level->init(map);

    //������ �������: �������������
    } else if (map[0] == QString("LEVEL: INVESTIGATION"))
    {
        LevelInvestigate * level = new LevelInvestigate(this);
        level->init(map);
    }
*/

    level = new LevelChase(this);
    level->init(levelMap1);

    //����� �� �����
    show();
}

void Game::nextLevel()
{
    qDebug() << "WE GOT A WINNER";
    levelNumber++;
    //Level * level = reinterpret_cast<Level *>(this->scene());
    level->clear();
    delete level;
    loadLevel();
}

void Game::resetLevel()
{
    qDebug() << "LOOK AT THIS LOOSER";
    //Level * level = reinterpret_cast<Level *>(this->scene());
    level->clear();
    //delete level;
    loadLevel();
}
