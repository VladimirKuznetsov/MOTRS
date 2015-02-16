#include <QApplication>
#include <QString>
#include "game.h"
#include "levelChase.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->loadLevel();
    game->show();

    return a.exec();
}
