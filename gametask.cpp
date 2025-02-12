#include "gametask.h"

GameTask::GameTask(QObject *parent) : QObject(parent)
{
    this->screenSize = QSize(default_w,default_h);
}
