#ifndef WIDGET_H
#define WIDGET_H

#include<QLabel>
#include <QWidget>
#include <QEvent>
#include "game.h"

#include "Admob/QmlBanner.h"
#include"Admob/QmlInterstitialAd.h"
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
    bool checkIsInContentArea(QPoint scroll);

    QmlBanner *banner;
    QmlInterstitialAd *interstitial;
    void loadAds();
    void loadInterstitialAd();
    void levelEndAds();

    QLabel *loadingLevelProgressLabel;
    void loadLevel();
    void loadLevelProgress();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPoint getHitPosition(QMouseEvent *event);
    void showLevelOnScene();
    void setLevelProgress(QString str);
    void levelFinishedShowMessageBox();
    void levelsIncrementer();
};

#endif // WIDGET_H
