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
        qDebug()<<"current position for level increment"<<pos<<" total levels length"<<levelsList.length();
        if (pos>=0 and pos<levelsList.length()-1){
            return levelsList[pos+1];
        }
        return levelsList.last();
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
        //this brilliant code does not work on android
//        qDebug()<<"Available LEVELS";
//        QString startPath=QString(":/img");//:/img/
//        QDir dir(startPath);

//        QStringList result;
//        QFileInfoList fil=dir.entryInfoList();
//        for (QFileInfo i:fil){
//            QString s=i.filePath();
//            result.append(s);
//        }
//        result.removeOne(":/img/screen");
//        qDebug()<<result;
//        return result;

        //SECOND TRY to write brilliant code
//        // Specify directory with leading ":"
//        QDir myDir("qrc:/img/");

//        // Specify selection criteria (empty list if you want all files)
//        const QStringList sel = QStringList({"*"});

//        // read files (and ignore directories) that match selection criteria
//        QStringList dirs;
//        for(QString dirName:myDir.entryList(sel,QDir::Dirs)){
//            dirs.append(myDir.path()+"/"+dirName);
//        }

//        qDebug()<<"DIRS"<<dirs;
//        dirs.removeOne(":/img/screen");
//        return dirs;

        QStringList result;
        result.append(":/img/testLevel1");
        result.append(":/img/testLevel2");

        result.append(":/img/WelcomePackLevel1");
        result.append(":/img/WelcomePackLevel2");
        result.append(":/img/WelcomePackLevel3");
        result.append(":/img/WelcomePackLevel4");
        result.append(":/img/WelcomePackLevel5");
        result.append(":/img/WelcomePackLevel6");
        result.append(":/img/WelcomePackLevel7");
        result.append(":/img/WelcomePackLevel8");
        result.append(":/img/WelcomePackLevel9");
        result.append(":/img/WelcomePackLevel10");


        result.append(":/img/InPrison1");
        result.append(":/img/InPrison2");
        result.append(":/img/InPrison3");
        result.append(":/img/InPrison4");
        result.append(":/img/InPrison5");
        result.append(":/img/InPrison6");
        result.append(":/img/InPrison7");
        result.append(":/img/InPrison8");
        result.append(":/img/InPrison9");
        result.append(":/img/InPrison10");

        return result;
    }

};

QStringList GameProgress::levelsList=GameProgress::getLevels();

QString GameProgress::filename="finished.txt";

}
#endif // GAMEPROGRESS_H
