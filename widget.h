#ifndef WIDGET_H
#define WIDGET_H

#include<QLabel>
#include <QWidget>
#include <QEvent>
#include "game.h"
#include "gametask.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Game *game;
    //for moving
    bool mMouseDragging;
    QPoint mLastMouseDragLocation;
    QPoint delta;
    //for multitach
    QEvent::Type m_eLastEventType;
//    void loadWalkedCat();
    bool checkIsInContentArea(QPoint scroll);
    QLabel *loadingLevelProgressLabel;
    void loadLevel();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint getHitPosition(QMouseEvent *event);
    void showLevelOnScene();
    void setLevelProgress(QString str);
};

#endif // WIDGET_H
