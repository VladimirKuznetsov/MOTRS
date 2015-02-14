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

    levelNumber = 3;
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 1100;
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //настраиваем параметры отображения окна
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
        "Сегодня ночью из Московского зоопарка сбежал редкий полосатый тюлень.",
        "Моя задача отыскать его и вернуть домой. Но с чего начать?",
        "Куда пойдёт огромный полосатый тюлень в большом городе?",
        "Сосредоточься, Даша! Ты должна думать как тюлень.",
        "---",
        "Итак, наш главный подозреваемый это пропавший сторож...",
        "Ночью он мог открыть дверь клетки, выманить тюленя мячом и похитить...",
        "Но зачем ему это? И где его теперь искать?",
        "...",
        "Шесть часов вечера, пора домой. Вот только разошлю ориентировку на сторожа.",
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
        "Опять провозилась с протоколами до позднего вечера.",
        "Всё бы сейчас отдала за чашку хорошего кофе...",
        "---",
        "Это был странный день. Пора с ним заканчивать.",
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
        "*БАХ!*",
        "Три часа ночи... кто станет ломиться в дверь в такое время?",
        "---",
        "Старый склад... Думаю, я знаю, где это.",
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
        "Не нравится мне это место...",
        "Нужно быстро тут всё проверить и возвращаться.",
        "---",
        "Похоже, что недавно здесь действительно держали тюленя.",
        "Хотела бы я знать, кто и зачем привёл меня сюда...",
        "*РЁВ ДВИГАТЕЛЯ*",
        "Что за чёрт?",
        "---",
        "%",
    };

    QString levelMap4[] =
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
        "Нужно разобраться с этим делом побыстрее.",
        "---",
        "Итак, наша лучшая зацепка это пропавший сторож...",
        "Но где его искать?",
        "...",
        "Как? Уже шесть вечера?!",
        "Сторожем займусь завтра на свежую голову, а сейчас домой.",
        "---",
        "%",
    };

    QString map[50];

    //загружаем интересующую нас карту в map[]
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

        case 3:
            if (levelMap3[i] != "%")
            {
                map[i] = levelMap3[i];
            } else
            {
                i = 50;
            }
            break;

        case 4:
            if (levelMap4[i] != "%")
            {
                map[i] = levelMap4[i];
            } else
            {
                i = 50;
            }
            break;

        default:
            break;
        }
    }

    //создаём уровень: погоня
    if (map[0] == QString("LEVEL: CHASE"))
    {
        level = new LevelChase(this);
        level->init(map);

    //создаём уровень: расследование
    } else if (map[0] == QString("LEVEL: INVESTIGATION"))
    {
        level = new LevelInvestigate(this);
        level->init(map);
    }

    //вывод на экран
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
