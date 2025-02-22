#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include<QDebug>
#include <QPoint>
#include <QPixmap>
#include"itemtype.h"

class Item
{
public:
    Item(){}
    Item(QPixmap pixmap,QPoint startPos,ItemType type){this->pixmap=pixmap;this->startPosition=startPos;this->type=type;}
    friend bool operator==(const Item& lhs, const Item& rhs){
        return (QString::compare(lhs.name,rhs.name)==0);
    }

    static Item getNewCheckedElem(){
        QString path=":/img/screen/checked.png";
        QPixmap img;
                img.load(path);

        Item i;
        i.pixmap=img;
        i.startPosition=QPoint(0,0);
        i.type=ItemType::image;
        i.name=path;
        i.size=QSize(0,0);

        return i;
    }

    QPoint startPosition;
    QPixmap pixmap;
    ItemType type;
    QString name;
    QSize size;

    QSize getSize(){return size;}
};
#endif // ITEM_H
