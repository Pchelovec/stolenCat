#include "level.h"

Level::Level(QObject *parent) : QObject(parent)
{

}

Item Level::getBuckground() const
{
    return buckground;
}

void Level::setBuckground(const Item &value)
{
    buckground = value;
}
