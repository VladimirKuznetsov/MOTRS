#include "game.h"
#include <math.h>
#include <QDebug>
#include <QVector>
#include <QTextCodec>
#include "levelChase.h"
#include "levelInvestigate.h"
#include "levelIntro.h"

Game::Game()
{
    showFullScreen();
    levelNumber = 0;
    WINDOW_HEIGHT = height();
    WINDOW_WIDTH = width();
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);
    LARGE_FONT = WINDOW_WIDTH * 0.032;
    MEDIUM_FONT = LARGE_FONT * 0.7;
    SMALL_FONT = LARGE_FONT / 2;

    if (LARGE_FONT < 20) LARGE_FONT = 20;
    if (SMALL_FONT < 12) SMALL_FONT = 12;

    //настраиваем параметры отображения окна
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

void Game::loadLevel()
{
    QString levelMap0[] =
    {
        "LEVEL: INTRO",
        "---",
        "230 230 230",
        "---",
        "Дарья Винокурова",
        "---",
        "по следам полосатого тюленя",
        "%",
    };

    QString levelMap1[] =
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
        "t      H n      b p  B c          o       b   B        t",
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
        "Ночью он мог открыть дверь клетки и похитить тюленя...",
        "Но в чём мотив? И где его теперь искать?",
        "...",
        "Шесть часов вечера, пора домой. Вот только закончу с бумажной работой.",
        "---",
        "%",
    };

    QString levelMap2[] =
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

    QString levelMap3[] =
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

    QString levelMap4[] =
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

    QString levelMap5[] =
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
        "Это же машина зоопарка! Стоять! Полиция!",
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
        " ",
        "---",
        "—Господин Огурцов! Так это вы - тюлений вор?",
        "—У меня в багажнике трёхсоткилограммовый тюлень. Глупо что-либо отрицать.",
        "—Тогда давайте начистоту. Зачем вы похитили тюленя? Ради наживы?",
        "...",
        "—В последнее время дела в зоопарке идут не лучшим образом...",
        "Старые вольеры уже разваливаются, а новые строить не на что.",
        "Страховка за похищенного тюленя была нашей последней надеждой.",
        "Потом я, конечно, устроил бы счастливое воссоединение...",
        "...но на время тюлень должен был исчезнуть.",
        "—А что же сторож? Он, ведь, не согласился на вашу аферу.",
        "Как вы убрали его с дороги?",
        "—Отпустил погулять на денёк, пригрозил  уволить, если он проболтается...",
        "...так что ним всё в порядке.",
        "Более того, как я понимаю, это именно он подсказал вам, где искать тюленя.",
        "Больше об этом месте никто не знал.",
        "...",
        "Послушайте, Дарья, всё что я делал было в интересах зоопарка!",
        "Я ведь директор зоопарка, а не преступник!",
        "—Теперь это будет решать суд.",
        "---",
        " ",
        "---",
        "%",
    };

    QString map[100];

    //загружаем интересующую нас карту в map[]
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

    //создаём уровень: введение
    } else if (map[0] == QString("LEVEL: INTRO"))
    {
        level = new LevelIntro(this);
        ((LevelIntro *)level)->init(map);
    }

    //вывод на экран
    showFullScreen();
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
