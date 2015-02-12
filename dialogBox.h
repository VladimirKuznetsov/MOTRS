#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QGraphicsTextItem>
#include <QString>
#include <QFont>
#include <cell.h>

class DialogBox : public QGraphicsTextItem
{
    Q_OBJECT
public:
    DialogBox(QGraphicsItem *parent = 0);
    void nextLine();
    QString text[10];
    Cell * cell;
    unsigned short lineNumber;

    bool isOn;

public slots:
    void setDialog(QString _text[10]);
    void setDialog(Cell * _cell);
    void move();

signals:
    void interactionEnded(Cell * c);
    
};

#endif // DIALOGBOX_H
