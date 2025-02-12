#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include<QCoreApplication>
#include <QMap>
#include<QPixmap>
#include<QDebug>
#include <QPoint>
#include"item.h"
#include"itemtype.h"

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(QObject *parent = nullptr);

    void loadLevel1(QString levelName){
        map->clear();

        if (levelName=="testLevel"){
            qDebug()<<"Loading test level";

            load(":/img/testRoom.png",QPoint(0,0),QSize(1600, 857),ItemType::background);

            load(":/img/cactuses/cactus1.webp",QPoint(10,700),QSize(100,100),ItemType::image);
            load(":/img/cactuses/cactus2.webp",QPoint(1200,470),QSize(100,100),ItemType::image);
            load(":/img/cactuses/cactus3.webp",QPoint(300,300),QSize(100,100),ItemType::image);
            load(":/img/cactuses/cactus4.webp",QPoint(400,300),QSize(100,100),ItemType::image);
            load(":/img/cactuses/cactus5.webp",QPoint(1300,500),QSize(100,50),ItemType::image);

        }


    }

    QPixmap getRes(QString resPath){
        return map->find(resPath).value().pixmap;
    }
    bool contains(QString resPath){
        return map->contains(resPath);
    }

    QPixmap getBuckground(){
        QString key=":/img/testRoom.png";
        Item i=map->find(key).value();
        map->remove(key);
        return i.pixmap;
    }

    QList<Item> getImagesElemenstAsList(){
        QList<Item> result;
        for (auto it = map->keyValueBegin(); it != map->keyValueEnd(); ++it) {
            result.push_back(it.base().value());
        }
        return result;
    }

    Item getItemAndRemove(QString key){
        Item i=map->take(key);
        map->remove(key);
        return i;
    }
private:
    QMap<QString,Item> *map;
    void load(QString resPath,QPoint pos,QSize size, ItemType t){
        //load img
        QPixmap img;
                img.load(resPath);

        //insert to map
        Item item;
        item.pixmap=img;
        item.startPosition=pos;
        item.type=t;
        item.name=resPath;
        item.size=size;

        map->insert(resPath, item);
        //for progress resolving
        QCoreApplication::instance()->processEvents(QEventLoop::AllEvents);
    }

};

#endif // LOADER_H
