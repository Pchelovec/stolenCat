#include "screen.h"
#include<QScreen>
#include<QGuiApplication>
#include<QDebug>
Screen::Screen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();
    qDebug()<<"Coustructor size of screen"<<screenGeometry;

}
