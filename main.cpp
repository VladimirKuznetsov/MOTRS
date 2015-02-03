#include <QtGui/QApplication>
#include <QString>
#include "game.h"

QString levelMap[] = {
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "         f                    ",
    "            f          f      ",
    "                              ",
    "      fff      f   f   ff     ",
    "ffffffffffffffffffffffffffffff",
};

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    game = new Game();
    game->init(levelMap);
    game->show();

    return a.exec();
}
