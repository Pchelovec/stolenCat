#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include<QCoreApplication>
#include <QMap>
#include<QFile>
#include<QPixmap>
#include<QDebug>
#include <QPoint>
#include"item.h"
#include"itemtype.h"

class Loader
{
public:
    Loader(){map=new QMap<QString,Item>;}

    void loadLevel1(QString levelName){
        map->clear();

        //STEP 1 LOAD FROM FILE
        qDebug()<<"Loading "<<levelName;
        QFile file(levelName+"/level.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QStringList list;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            list.append(line);
        }
        qDebug()<<list;


        //STEP 2 LOAD BACKGROUND
        QString firstLine_Background=list[0];
        QStringList bacground=firstLine_Background.split(" ");
        QString resPath=levelName+"/"+bacground[0];
        QPixmap img;
        img.load(resPath);
        load(resPath,QPoint(bacground[1].toInt(),bacground[1].toInt()),QSize(img.width(), img.height()),ItemType::background);
        list.pop_front();

        //STEP 3 LOAD EITEMS
        for(QString itemedString:list){
            QStringList olmostItem=itemedString.split(" ");
            QString b=levelName+"/"+olmostItem[0];
            qDebug()<<olmostItem;
            load(b,QPoint(olmostItem[1].toInt(),olmostItem[2].toInt()),QSize(olmostItem[3].toInt(), olmostItem[4].toInt()),ItemType::image);
        }

    }

    QPixmap getRes(QString resPath){
        return map->find(resPath).value().pixmap;
    }
    bool contains(QString resPath){
        return map->contains(resPath);
    }

    Item getBuckground(){
        //        QString key=":/img/testLevel1/testRoom.png";
        //        Item i=map->find(key).value();
        //        map->remove(key);
        //        return i;
        Item result;
        for(QString mapKey:map->keys()){
            Item e=map->find(mapKey).value();
            if (e.type==ItemType::background){
                result=e;
                map->remove(mapKey);
            }
        }
        return result;
    }

    QList<Item> getImagesElemenstAsList(QString levelName){
        QList<Item> result;

        //STEP 1 LOAD FROM FILE
        qDebug()<<"Loading "<<levelName;
        QFile file(levelName+"/level.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QList<Item>();

        QStringList list;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            list.append(line);
        }
        qDebug()<<list;


        //STEP 2 DEL BACKGROUND
       list.pop_front();

        //STEP 3 LOAD ITEMS
        for(QString itemedString:list){
            QStringList olmostItem=itemedString.split(" ");
            QString b=levelName+"/"+olmostItem[0];
            result.push_back(map->find(b).value());
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
