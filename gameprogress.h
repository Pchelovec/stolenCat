#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QString>
#include<QDebug>
#include<QFile>
#include<QDirIterator>
namespace  {

class GameProgress
{
public:
    GameProgress();
    static QString filename;

    static QStringList levelsList;

    static QStringList levels(){return levelsList;}

    static int getLevelsCount(){return levelsList.size();}

    static int getPosition(QString level){
        int result=0;

        for (QString s:levelsList){
            if (QString::compare(s,level)==0){return result;}
            result++;
        }
        return -1;//no such element
    }

    static QString getNextForCurrentPosition(QString current){
        int pos=getPosition(current);
        if (pos>=0 and pos<levelsList.size()-1){
            return levelsList.at(pos+1);
        }
        return "winner";
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


private:
    static QStringList getLevels(){
//        qDebug()<<"Available LEVELS";
        QString startPath=QString(":/img/");
        QDir dir(startPath);

        QStringList result;
        QFileInfoList fil=dir.entryInfoList();
        for (QFileInfo i:fil){
            QString s=i.filePath();
            result.append(s);
        }
        result.removeOne(":/img/screen");
//        qDebug()<<result;
        return result;
    }

};

QStringList GameProgress::levelsList=GameProgress::getLevels();

QString GameProgress::filename="finished.txt";

}
#endif // GAMEPROGRESS_H
