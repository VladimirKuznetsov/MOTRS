#include <QtGui/QApplication>
#include <QString>
#include "game.h"

QString levelMap[] = {
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "  p   hhh e    h   h   hh     h                      h         h h             ",
    "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
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
