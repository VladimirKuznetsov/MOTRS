#ifndef DIALOGBOX_H
#define DIALOGBOX_H

#include <QString>
#include <QFont>
#include <cell.h>

class DialogBox : public QGraphicsTextItem
{
    Q_OBJECT
public:
    DialogBox(QGraphicsObject *parent = 0);
    void nextLine();
    void skip();
    QString text[30];
    Cell * cell;
    unsigned short lineNumber;

    bool isOn;

public slots:
    void setDialog(QString _text[10]);
    void setDialog(Cell * _cell);
    void move();

signals:
    void ended(Cell * c);
    void ended();
    
};

#endif // DIALOGBOX_H
