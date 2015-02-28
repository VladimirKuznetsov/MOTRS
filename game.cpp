#include "game.h"
#include <math.h>
#include <QVector>
#include "levelChase.h"
#include "levelInvestigate.h"
#include "levelIntro.h"
#include <typeinfo>
#include <qscreen.h>
#include <QApplication>
#include <QFontMetrics>
//#include <QDebug>

Game::Game()
{

    //под windows включаем управление с клавиатуры
#if defined(WIN32)
    platformZoom = 1;
    control_mode = keyboard;

    //под мобильные платформы используем тачскрин
#else
    platformZoom = 1.2;
    control_mode = mouse;
#endif

    levelNumber = 0;
    QScreen * screen = QApplication::screens().at(0);
    WINDOW_HEIGHT = screen->size().height();
    WINDOW_WIDTH = screen->size().width();
    CELL_SIZE = WINDOW_HEIGHT / 15;
    GRAVITY = ceil(float(CELL_SIZE) / 60);

    //подстройка размера шрифтов под экран
    SMALL_FONT = 12;

    QFont sFont("Calibri", SMALL_FONT);
    QFontMetrics fm(sFont);
    QString longLine("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ");

    //увеличиваем шрифт пока строка максимальной длины
    //не выйдет за допустимые размеры поля
    while (fm.width(longLine) < WINDOW_WIDTH - CELL_SIZE * 2)
    {
        SMALL_FONT++;
        sFont = QFont("Calibri", SMALL_FONT);
        fm = QFontMetrics(sFont);
    }
    SMALL_FONT -= 1;

    LARGE_FONT = SMALL_FONT * 2;
    MEDIUM_FONT =  SMALL_FONT * 1.4;

    //настраиваем параметры отображения окна
    setStyleSheet( "QGraphicsView { border-style: none; }" );
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    scale(platformZoom, platformZoom);
}


void Game::mousePressEvent(QMouseEvent * event)
{
    if (typeid(*level) == typeid(LevelChase))
    {
        ((LevelChase *)level)->mousePressEvent(event);
    } else if (typeid(*level) == typeid(LevelInvestigate))
    {
        ((LevelInvestigate *)level)->mousePressEvent(event);
    } else if (typeid(*level) == typeid(LevelIntro))
    {
        ((LevelIntro *)level)->mousePressEvent(event);
    } else
    {
        level->mousePressEvent(event);
    }
}


void Game::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (typeid(*level) == typeid(LevelChase))
    {
        ((LevelChase *)level)->mouseDoubleClickEvent(event);
    } else if (typeid(*level) == typeid(LevelInvestigate))
    {
        ((LevelInvestigate *)level)->mouseDoubleClickEvent(event);
    } else if (typeid(*level) == typeid(LevelIntro))
    {
        ((LevelIntro *)level)->mouseDoubleClickEvent(event);
    } else
    {
        level->mouseDoubleClickEvent(event);
    }
}

void Game::loadLevel()
{
    QString levelMap0[] =
    {
        "LEVEL: INTRO",
        "---",
        "230 230 230",
        "---",
        tr("Dasha Vinokurova"),
        "---",
        tr("Mystery of the Ribbon Seal"),
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
        "ffffffffffffgfffffffffffffffffffffffffffffffffffffffffff",
        "---",
        "cno",
        "---",
        tr("A rare ribbon seal disappeared this night from the Moscow zoo."),
        tr("My job is to get him back home. But what should I start with?"),
        "Куда пойдёт огромный полосатый тюлень в большом городе?",
        "Сосредоточься, Даша! Ты должна думать как тюлень.",
        "---",
        "Итак, наш главный подозреваемый это пропавший сторож...",
        "Ночью он мог открыть дверь клетки и похитить тюленя...",
        "Но в чём мотив? И где его теперь искать?",
        "...",
        "Шесть часов вечера, пора домой. Вот только закончу с бумажной работой.",
        "---",
        "1",
        "---",
        "%",
    };

    QString levelMap2[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "190 180 110",
        "---",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "TTTTTTTTTTTTTTTTSSSS",
        "w               RSSS",
        "w               RSSS",
        "w               RSSS",
        "w  p  k     i   RSSS",
        "WWWWWWWWWWWWWWWWSSSS",
        "SSSSSSSSSSSSSSSSSSSS",
        "---",
        "k",
        "---",
        "Опять провозилась с протоколами до позднего вечера.",
        "Всё бы сейчас отдала за чашку хорошего кофе...",
        "---",
        "Это был странный день. Пора с ним заканчивать.",
        "---",
        "2.5",
        "---",
        "%",
    };

    QString levelMap3[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "110 110 115",
        "---",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFF",
        "UUUUUUUUUUUUUUUUFFFF",
        "w               rFFF",
        "w               rFFF",
        "w               rFFF",
        "ta    K     IP  rFFF",
        "CCCCCCCCCCCCCCCCFFFF",
        "FFFFFFFFFFFFFFFFFFFF",

        "---",
        "a",
        "---",
        "*БАХ!*",
        "Три часа ночи... кто станет ломиться в дверь в такое время?",
        "---",
        "Старый склад... Думаю, я знаю, где это.",
        "---",
        "2.5",
        "---",
        "%",
    };

    QString levelMap4[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "80 80 80",
        "---",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "UUUUUUUUUUUUUUUUUUUUUUUUUUUUU",
        "w                     d     w",
        "w                           w",
        "w      q   j                w",
        "w                           w",
        "wV  p  jLZ j   q zs   Q z   t",
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "---",
        "ds",
        "---",
        "Не нравится мне это место...",
        "Нужно быстро тут всё проверить и возвращаться.",
        "---",
        "Похоже, что недавно здесь действительно держали тюленя.",
        "Хотела бы я знать, кто и зачем привёл меня сюда...",
        "*РЁВ ДВИГАТЕЛЯ*",
        "Что за чёрт?",
        "---",
        "2.5",
        "---",
        "%",
    };

    QString levelMap5[] =
    {
        "LEVEL: CHASE",
        "---",
        "20 20 50",
        "---",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w                                                                                                                                                                                     ",
        "w p    v            h     h     hh               hhh         h      h            h h         h    h h       hhh          h h        h          hh         h         h h               ",
        "ffffffffffffffffffffffffgfffffffffffffffffffffffffffffffffygffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffgfffffffffffffffffffffffffffffffffffffffff",
        "---",
        "h  ",
        "---",
        "Это же машина зоопарка! Стоять! Полиция!",
        "---",
        " ",
        "---",
        "1",
        "---",
        "%",
    };

    QString levelMap6[] =
    {
        "LEVEL: INVESTIGATION",
        "---",
        "20 20 50",
        "---",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                            w",
        "w                     E      w",
        "w  p O                       w",
        "ffffffffffffffffffffffffffffff",
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
        "—А что же сторож? Он ведь не согласился на вашу аферу.",
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
        "2.5",
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
        ((LevelChase *)level)->init(map);

    //создаём уровень: расследование
    } else if (map[0] == QString("LEVEL: INVESTIGATION"))
    {
        level = new LevelInvestigate(this);
        ((LevelInvestigate *)level)->init(map);

    //создаём уровень: введение
    } else if (map[0] == QString("LEVEL: INTRO"))
    {
        level = new LevelIntro(this);
        ((LevelIntro *)level)->init(map);
    }

    //вывод на экран
    showFullScreen();
}

double Game::zoom()
{
    return level->zoom * platformZoom;
}

void Game::nextLevel()
{
    //рассчитываем коэффициент отдаления
    double zoomOut = 1 / level->zoom;

    //удаляем предыдущий уровень
    levelNumber++;
    delete level;

    //отдаляем камеру в начальное положение
    scale(zoomOut, zoomOut);

    //загружаем следующий уровень
    loadLevel();
}

void Game::resetLevel()
{
    //рассчитываем коэффициент отдаления
    double zoomOut = 1 / level->zoom;

    //удаляем предыдущий уровень
    delete level;

    //отдаляем камеру в начальное положение
    scale(zoomOut, zoomOut);

    //загружаем уровень повторно
    loadLevel();
}
