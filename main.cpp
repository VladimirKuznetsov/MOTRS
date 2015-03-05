#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QDebug>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translate;

    translate.load("motrs_" + QLocale::system().name(), ":/translations");
    a.installTranslator(&translate);

    game = new Game();
    game->loadLevel();
    game->show();

    return a.exec();
}
