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

    levelNumber = 5;
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
        "t     H  n      b p  B c          o       b   B        t",
        "fffffyfffffgffffffffffffffffffffffffffyffffffffffffffgff",
        "---",
        "cno",
        "---",
        "������� ����� �� ����������� �������� ������ ������ ��������� ������.",
        "��� ������ �������� ��� � ������� �����. �� � ���� ������?",
        "���� ����� �������� ��������� ������ � ������� ������?",
        "�������������, ����! �� ������ ������ ��� ������.",
        "---",
        "����, ��� ������� ������������� ��� ��������� ������...",
        "����� �� ��� ������� ����� ������ � �������� ������...",
        "�� � ��� �����? � ��� ��� ������ ������?",
        "...",
        "����� ����� ������, ���� �����. ��� ������ ������� � �������� �������.",
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
        "w  P    k               i         RSSS",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWSSSS",
        "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
        "---",
        "ik",
        "---",
        "����� ����������� � ����������� �� �������� ������.",
        "�� �� ������ ������ �� ����� �������� ����...",
        "---",
        "��� ��� �������� ����. ���� � ��� �����������.",
        "---",
        "%",
    };

    QString levelMap2[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "110 110 115",
        "---",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUFFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "w                                 rFFF",
        "ta     K               i  P       rFFF",
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "---",
        "a",
        "---",
        "*���!*",
        "��� ���� ����... ��� ������ �������� � ����� � ����� �����?",
        "---",
        "������ �����... �����, � ����, ��� ���.",
        "---",
        "%",
    };

    QString levelMap3[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "80 80 80",
        "---",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU",
        "w                                                               w",
        "w                                                               w",
        "w                                                 d             w",
        "w                                                               w",
        "w                                                               w",
        "w                                                               w",
        "w           q                      j   q                        w",
        "w                                                               w",
        "w                                                               w",
        "w                                                               w",
        "w V   P     j L Z       j        s q   z          Q   z         t",
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "---",
        "Lds",
        "---",
        "�� �������� ��� ��� �����...",
        "����� ������ ��� �� ��������� � ������������.",
        "---",
        "������, ��� ������� ����� ������������� ������� ������.",
        "������ �� � �����, ��� � ����� ����� ���� ����...",
        "*Ш� ���������*",
        "��� �� ����?",
        "---",
        "%",
    };

    QString levelMap4[] =
    {
        "LEVEL: CHASE",
        "---",
        "20 20 50",
        "---",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w                                                                                                                                             ",
        "w p    v    h     h     hh               hhh         h      h            h h         h    h h       hhh          h h        h          hh     ",
        "ffffffffffffffgffffffffffffffffffyfffffffffffffffygfffffffffffffffffffffffffffffffffffffffffffffyffffffffffffffffffffffffffffffffffgffffffffff",
        "---",
        "h  ",
        "---",
        "��� �� ������ ��������! ������! �������!",
        "---",
        " ",
        "---",
        "%",
    };

    QString levelMap5[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "20 20 50",
        "---",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                                                   w",
        "w                            E                      w",
        "w                                                   w",
        "w                                                   w",
        "w     P         O                                   w",
        "fffffffffffffffffffffffffffffffffffffffffffffffffffff",
        "---",
        "a",
        "---",
        "��������� �������! ��� ��� �� - ������� ���?",
        "�� ���� � ��������� ������������������� ������. ����� ���-���� ��������.",
        "������ ������� ���������. ����� �� �������� ������? ���� ������?",
        "...",
        "�� ��������� ����� ���� � �������� ���� �� ������ �������...",
        "������ ������� ��� �������������, � ����� ������� �� �� ���.",
        "��������� �� ����������� ������ ���� ����� ��������� ��������.",
        "����� �, �������, ������� �� ���������� �������������...",
        "...�� �� ����� ������ ������ ��� ���������.",
        "�� ��� �� ������? ��, ����, �� ���������� �� ���� �����.",
        "��� �� ������ ��� � ������?",
        "��������� �������� �� ����, ���������  �������, ���� �� ������������...",
        "...��� ��� ��� �� � �������.",
        "����� ����, ��� � �������, ��� ������ �� ��������� ���, ��� ������ ������.",
        "������ �� ���� ����� ����� �� ����.",
        "...",
        "����������, �����, �� ��� � ����� ���� � ��������� ��������!",
        "� ���� �������� ��������, � �� ����������!",
        "������� ��� ����� ������ ���.",
        "---",
        " ",
        "---",
        "%",
    };

    QString levelMap6[] =
    {
        "LEVEL: INVESTIGATION",
                "---",
                "20 20 50",
                "---",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w                                    w",
                "w     P   O                          w",
                "ffffffffffffffffffffffffffffffffffffff",
                "---",
                "a",
                "---",
                "-�������� �������! ��� ��� �� - ������� ���?",
                "-� ���� � ��������� ������������������� ������. ����� ���-���� ��������.",
                "-����� ������� ���������. ����� �� �������� ������? ���� ������?",
                "...",
                "-� ��������� ����� ���� � �������� ���� �� ������ �������...",
                "������ ������� ��� �������������, � ����� ������� �� �� ���.",
                "��������� �� ����������� ������ ���� ����� ��������� ��������.",

        "---",
        "������ �����... �����, � ����, ��� ���.",
        "---",
        "%",
    };

    QString map[100];

    //��������� ������������ ��� ����� � map[]
    for (int i = 0; i < 100; i++)
    {
        switch (levelNumber)
        {

        case 0:
            if (levelMap0[i] != "%")
            {
                 map[i] = levelMap0[i];
            } else
            {
                i = 100;
            }
            break;

        case 1:
            if (levelMap1[i] != "%")
            {
                map[i] = levelMap1[i];
            } else
            {
                i = 100;
            }
            break;

        case 2:
            if (levelMap2[i] != "%")
            {
                map[i] = levelMap2[i];
            } else
            {
                i = 100;
            }
            break;

        case 3:
            if (levelMap3[i] != "%")
            {
                map[i] = levelMap3[i];
            } else
            {
                i = 100;
            }
            break;

        case 4:
            if (levelMap4[i] != "%")
            {
                map[i] = levelMap4[i];
            } else
            {
                i = 100;
            }
            break;

        case 5:
            if (levelMap5[i] != "%")
            {
                map[i] = levelMap5[i];
            } else
            {
                i = 100;
            }
            break;

        case 6:
            if (levelMap6[i] != "%")
            {
                map[i] = levelMap6[i];
            } else
            {
                i = 100;
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
    delete level;
    loadLevel();
}

void Game::resetLevel()
{
    qDebug() << "LOOK AT THIS LOOSER";
    delete level;
    loadLevel();
}
