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

    Item getBuckground() const;
    void setBuckground(const Item &value);

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


    void clear()
    {
        elements.clear();
        toFind.clear();
        items.clear();
    }

    void loadLevel(QString levelName){
        clear();
        loader.loadLevel1(levelName);
        buckground=loader.getBuckground();
        elements=loader.getImagesElemenstAsList(levelName);
        toFind=loader.getImagesElemenstAsList(levelName);
        items.push_back(elements[0]);
        items.push_back(elements[1]);
        items.push_back(elements[2]);

        toFind.pop_front();
        toFind.pop_front();
        toFind.pop_front();

        //final checkes
        toFind.push_back(Item::getNewCheckedElem());
        toFind.push_back(Item::getNewCheckedElem());
        toFind.push_back(Item::getNewCheckedElem());

        qDebug()<<"toFindSize:"<<toFind.size();
        qDebug()<<"ELEMENTS"<<elements.size();
        qDebug()<<"items"<<items.size();
    }

    QList<Item> getElements(){return elements;}

    void setNewSearchedItem(){
        qDebug()<<items[0].name;
        qDebug()<<items[1].name;
        qDebug()<<items[2].name;

        qDebug()<<"elements size:"<<toFind.size();

//        if (items[0].name==""){del(items[0]);}//toFind.pop_front();
//        if (items[1].name==""){del(items[1]);}
//        if (items[2].name==""){del(items[2]);}

    }

    void delElem1(){Item removedItem=items[0];del(removedItem);
                    items[0]=get();
//                    setNewSearchedItem();
                   }
    void delElem2(){Item removedItem=items[1];del(removedItem);
                    items[1]=get();
//                    setNewSearchedItem();
                   }
    void delElem3(){Item removedItem=items[2];del(removedItem);
                    items[2]=get();
//                                setNewSearchedItem();
                   }

    int toFindSize(){return toFind.size();}
private:
    QList<Item> items;//searched elem
    Item buckground;
    QList<Item> elements;//all elem
    QList<Item> toFind;//all elem to find

    Loader loader;

    void del(Item i){
        qDebug()<<"remove"<<i.name;
        elements.removeOne(i);
    }

    Item get(){
        Item i=toFind.front();toFind.pop_front();return i;
    }
};

#endif // LEVEL_H
