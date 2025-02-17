#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QString>
#include<QDebug>
#include<QFile>
#include<QDirIterator>

class GameProgress
{
public:
    GameProgress();
    static QString filename;

    static QStringList getLevels(){
        qDebug()<<"Available LEVELS";
        QString startPath=QString(":/img/");
        QDir dir(startPath);

        QStringList result;
        QFileInfoList fil=dir.entryInfoList();
        for (QFileInfo i:fil){
            QString s=i.filePath();
            result.append(s);
        }
        result.removeOne(":/img/screen");
        qDebug()<<result;
        return result;
    }

    static bool checkLevel(QString path){
        qDebug()<<"checking:"<<path;
        QString txtDataFileName="/level.txt";

        QString fullPath=path+txtDataFileName;
        QFile f(fullPath);
        if (f.exists()){qDebug()<<"EXIST"<<fullPath;}
        return f.exists();
    }

    static void loadFromFiles(QString path){
        qDebug()<<"TODO loading for path"<<path;
    }
};

#endif // GAMEPROGRESS_H
