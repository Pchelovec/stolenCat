#include "level.h"

Level::Level(QObject *parent) : QObject(parent)
{

}

QPixmap Level::getBuckground() const
{
    return buckground;
}

void Level::setBuckground(const QPixmap &value)
{
    buckground = value;
}
