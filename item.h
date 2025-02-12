#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include"itemtype.h"

class Item
{
public:
    Item();
    Item(QPixmap pixmap,QPoint startPos,ItemType type){this->pixmap=pixmap;this->startPosition=startPos;this->type=type;}
    QPoint startPosition;
    QPixmap pixmap;
    ItemType type;
    QString name;
    QSize size;

    QSize getSize(){return size;}
};

#endif // ITEM_H
