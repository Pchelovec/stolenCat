#ifndef PROGRESS_H
#define PROGRESS_H

#include <QString>
#include<QFile>
#include<QTextStream>
#include<QFileInfo>
#include<QDebug>
#include "language.h"
namespace  {

class Progress
{
private:

public:
    Progress(){}
    static QString filename;

    static bool saveProgress(QString last_passes_level, supportedLanguage lang){
        bool result;
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            qDebug()<<"Applicaction language is "<<lang;
            qDebug()<<"Progerss save level"<<last_passes_level;
            QTextStream stream( &file );
            stream << last_passes_level <<endl;
            stream << lang <<endl;
            result=true;
        }
        file.close();
        return result;
    }

    //return lastPassedLevel and lang
    static QPair<QString,int> loadProgress(){
        QPair<QString,int> result;

        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            QString level;
            int lang;
            QTextStream stream( &file );
            stream>>lang;
            stream>>level;
            qDebug()<<"Dessirialized level-"<<level;
            qDebug()<<"restored lang "<<lang;
//            state->setLevelAndScene((Level)level,Screen(scene));
            return QPair<QString,int>(level,lang);
        }
        return QPair<QString,int>("error",0);
    }

    static bool removeProgress(){
        QFile::remove(filename);
    }

    static bool progressExist(){
        QFileInfo check_file(filename);
        // check if file exists and if yes: Is it really a file and not a directory?
        if (check_file.exists() && check_file.isFile()) {
            return true;
        }
        return false;
    }
};
QString Progress::filename="finished.txt";
}

#endif // PROGRESS_H
