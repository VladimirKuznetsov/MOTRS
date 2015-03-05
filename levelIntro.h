#ifndef LEVELINTRO_H
#define LEVELINTRO_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QString>
#include "level.h"

class LevelIntro : public Level
{
    Q_OBJECT
public:
    LevelIntro(QGraphicsView * parent);
    void init(QString map[]);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    int step;

signals:
public slots:
    void checkRules();
};

#endif // LEVELINTRO_H
