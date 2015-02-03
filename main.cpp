#include <QtGui/QApplication>
#include <QString>
#include "game.h"

QString levelMap[] = {
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "            h          f      ",
    "                              ",
    "  p   hhh      h   h   hh     ",
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
