#include "screen.h"
#include<QScreen>
#include<QGuiApplication>
Screen::Screen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();


}
