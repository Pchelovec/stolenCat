#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPixmap>
#include "gametask.h"
#include "patched_game_painter.h"
#include"level.h"
#include"screen.h"
class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void loadLevel(QString name);
    bool hit(QPoint pos);
    bool changed;

    QPixmap * getScene(GameTask *task);
    QPixmap getItem0();
    QPixmap getItem1();
    QPixmap getItem2();

    Screen getScreen(){return screen;}


private:

    QPixmap getResImg(QString path, QSize screen_size);
    QPixmap getResImg(QString path);
    Level level;
    Screen screen;
    QRect createRectByItem(Item item);
};

#endif // GAME_H
