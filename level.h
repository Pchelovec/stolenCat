#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include<QPixmap>
#include<QList>
#include"loader.h"
#include"item.h"
class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = nullptr);

    QPixmap getBuckground() const;
    void setBuckground(const QPixmap &value);

    Item getItem0(){return items[0];}
    Item getItem1(){return items[1];}
    Item getItem2(){return items[2];}

    bool isItemHit(QPoint hitPosition){
        return (checkHitForItem(hitPosition, 0) or
                (checkHitForItem(hitPosition,1)) or
                (checkHitForItem(hitPosition,2)));
    }

    bool checkHitForItem(QPoint hitPosition,int i){
        int x=items[i].startPosition.x();
        int y=items[i].startPosition.y();

        int x2=items[i].startPosition.x()+items[i].pixmap.width();
        int y2=items[i].startPosition.y()+items[i].pixmap.height();

        if ((hitPosition.x()>=x and hitPosition.x()<=x2)
                and (hitPosition.y()>=y and hitPosition.y()<=y2)) return true;
    }
    bool loadedAsMemoryRes(QString resPath){return loader.contains(resPath);}
    QPixmap getLoadedRes(QString resPath){return loader.getRes(resPath);}


    void loadLevel(QString levelName){
        loader.loadLevel1(levelName);
        buckground=loader.getBuckground();
        elements=loader.getImagesElemenstAsList();
        items.push_back(elements[0]);
        items.push_back(elements[1]);
        items.push_back(elements[2]);

        //remove from stored items
//        loader.getItemAndRemove(elements[0].);
    }

    QList<Item> getElements(){return elements;}
private:
    QList<Item> items;
    QPixmap buckground;
    QList<Item> elements;

    Loader loader;

};

#endif // LEVEL_H
