#include "game.h"

#include<QDebug>
Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::loadLevel(QString name)
{
    level.loadLevel(name);
}

bool Game::hit(QPoint pos)
{
    qDebug()<<"User hit"<<pos;
    QRect mouse=QRect(pos.x(),pos.y(),1,1);
    QRect r1=createRectByItem(level.getItem0());qDebug()<<"rect1"<<r1;
    QRect r2=createRectByItem(level.getItem1());qDebug()<<"rect2"<<r2;
    QRect r3=createRectByItem(level.getItem2());qDebug()<<"rect3"<<r3;

    bool result=false;
    if (r1.intersects(mouse)){qDebug()<<"intersect with 1 item";level.delElem1();result=true;}
    if (r2.intersects(mouse)){qDebug()<<"intersect with 2 item";level.delElem2();result=true;}
    if (r3.intersects(mouse)){qDebug()<<"intersect with 3 item";level.delElem3();result=true;}
    return result;
}

QPixmap *Game::getScene()
{
    QSize screen=QSize(level.getBuckground().getSize().width(),level.getBuckground().getSize().height());
    PatchedGamePainter *gamePainter=new PatchedGamePainter(screen);
    gamePainter->create();
    gamePainter->draw(0,0,level.getBuckground().pixmap.scaled(screen));
    for (Item i:level.getElements()){
        qDebug()<<"painted "<<i.pixmap<<"("<<i.startPosition.x()<<":"<<i.startPosition.y()<<")";
        gamePainter->draw(i.startPosition.x(),i.startPosition.y(),getResImg(i.name,i.size));
    }
    return gamePainter->process();
}

QPixmap Game::getItem0()
{
    return level.getItem0().pixmap;
}

QPixmap Game::getItem1()
{
    return level.getItem1().pixmap;
}

QPixmap Game::getItem2()
{
    return level.getItem2().pixmap;
}

bool Game::levelFinished()
{
    return (level.toFindSize()==0);
}

void Game::saveProgress(QString passedLevel)
{
    Progress::saveProgress(passedLevel,supportedLanguage::EN);
}

QPixmap Game::getResImg(QString path, QSize screen_size)
{
    QPixmap pixmap;
    if (level.loadedAsMemoryRes(path)){pixmap=level.getLoadedRes(path);}
    else {qDebug()<<path<<" LOAD FROM DISK";pixmap.load(path);}
    return pixmap.scaled(screen_size.width(),screen_size.height());
}


QRect Game::createRectByItem(Item item)
{
    return QRect(item.startPosition.x(),item.startPosition.y(),
                       item.size.width(),item.size.height());
}
