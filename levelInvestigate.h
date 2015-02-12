#ifndef LEVELINVESTIGATE_H
#define LEVELINVESTIGATE_H

#include <QObject>
#include <QGraphicsView>
#include <QString>
#include "level.h"

class LevelInvestigate : public Level
{
    Q_OBJECT
public:
    LevelInvestigate(QGraphicsView * parent);
    void followPlayer();

signals:
public slots:
    void checkRules();
};

#endif // LEVELINVESTIGATE_H
