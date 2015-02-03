#include <QtGui/QApplication>
#include <QString>
#include "game.h"

Game * game;

QString levelMap[] = {
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "                              ",
    "gggggggggggggggggggggggggggggg",
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    game = new Game();
    game->init();
    game->show();

    return a.exec();
}
