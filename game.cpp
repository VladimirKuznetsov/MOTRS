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
    GRAVITY = ceil(float(CELL_SIZE) / 50) * 40;

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
    setOptimizationFlags( QGraphicsView::DontClipPainter  | QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing );

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

void Game::mouseReleaseEvent(QMouseEvent * event)
{

    if (typeid(*level) == typeid(LevelChase))
    {
        ((LevelChase *)level)->mouseReleaseEvent(event);
    } else if (typeid(*level) == typeid(LevelInvestigate))
    {
        ((LevelInvestigate *)level)->mouseReleaseEvent(event);
    } else if (typeid(*level) == typeid(LevelIntro))
    {
        ((LevelIntro *)level)->mouseReleaseEvent(event);
    } else
    {
        level->mouseReleaseEvent(event);
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
        tr("This night a rare ribbon seal ran away from the Moscow zoo."),
        tr("My job is to get him back home. But what should I start with?"),
        tr("Where would a giant ribbon seal go in a big city of Moscow?"),
        tr("Concentrate, Dasha! You gotta think like a seal."),
        "---",
        tr("So what do we have? It looks like our main suspect is the watchman."),
        tr("He could open the door of the cage and steal the seal at night."),
        tr("But what was the motive? And where would he hide the seal?"),
        "...",
        tr("It's 6 PM! Time to go home. I only need to finish with papers."),
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
        tr("Great. I spent whole evening messing around with documents."),
        tr("I'd kill for a cup of coffee now."),
        "---",
        tr("It was a strange day. I should have finished it long ago."),
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
        tr("*KNOCK KNOCK*"),
        tr("It's 3 AM. Who's that at the door?"),
        "---",
        tr("Old warehouse. I think I know where it is..."),
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
        tr("I don't like this place..."),
        tr("Better check it fast and get back home."),
        "---",
        tr("It seems like someone actually kept a seal here for some time."),
        tr("I wish I knew who led me here and why..."),
        tr("*SOUND OF THE MOTOR*"),
        tr("What the?.."),
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
        tr("What is this car doing here? Police! Freeze!"),
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
        tr("—Mr Ogurtsov! So you're the mysterious seal thiev?"),
        tr("—I got 300 kg seal in a trunk. That's quite a solid evidence."),
        tr("—So let's make it clear. Why did you steal the seal? For money?"),
        "...",
        tr("—Things haven't been going well in the zoo lately..."),
        tr("Old cages were falling apart and we did not have money to repair them."),
        tr("That's when I came up with this idea. Insuranse payments could have saved us!"),
        tr("I swear I was going to bring the seal back after we got the money..."),
        tr("...but for some time it had to vanish."),
        tr("—And what about the watchman? He didn't agree with this plan, did he?"),
        tr("But you found a way to make him disappear..."),
        tr("—I gave him a day off, threatened to fire him, if he'd say a word..."),
        tr("...so it seems to me he's perfectly fine now."),
        tr("Moreover I suppose he gave you the seal's location."),
        tr("Nobody else knew about this place."),
        "...",
        tr("Listen, Daria, all I did was for the zoo's best!"),
        tr("For the love of god! I'm a director of the zoo, not a criminal!"),
        tr("—That's for jury to judge."),
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
