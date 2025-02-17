#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
#include <QScreen>
#include <QDebug>

#include<QScrollBar>
#include"gameprogress.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    game=new Game();
    //loadWalkedCat();
    loadingLevelProgressLabel = new QLabel(this);
    ui->stackedWidget->setCurrentIndex(0);
    QStringList sl=GameProgress::getLevels();
    GameProgress::checkLevel(sl[0]);
    if (Progress::progressExist()){
        setLevelProgress(Progress::loadProgress().first);//setup restored progress
    }
    else {
        setLevelProgress(":/img/testLevel1");
    }
}

//void Widget::loadWalkedCat()
//{
//    QMovie *movie = new QMovie(":/img/cat0.gif");
//    movie->setScaledSize(QSize(600,400));//:/img/cat0.gif
//    ui->stackedWidget->currentWidget()->setStyleSheet("background-image:url(\"bkg.jpg\"); background-position: center;");
////    ui->label->setMovie(movie);
////    ui->label->setScaledContents(true);
////    ui->label->setToolTip("This cat was stolen");
//    movie->start();
//}

bool Widget::checkIsInContentArea(QPoint pos)
{
    qDebug()<<"just center"<<ui->contentLabel->geometry().center();
    if ((pos.x()<0)or (pos.y()<0))return false;
    if ((pos.x()>ui->contentLabel->geometry().width()) or(pos.y()>ui->contentLabel->geometry().height())) return false;

    return true;
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    mMouseDragging=true;

    if (event->button() == Qt::LeftButton)
    {

        mLastMouseDragLocation = event->pos();
        setCursor(Qt::CursorShape::OpenHandCursor);
    }

    if (ui->stackedWidget->currentIndex()==2){
        ui->stackedWidget->setCurrentIndex(0);
        //TODO MAKE SETTINGS FIELDS AND
                //SAVE SETTINGS
        return;
    }

    if (ui->stackedWidget->currentIndex()==1){
        //HIT
        QPoint p=getHitPosition(event);
        if (checkIsInContentArea(p)){
            bool b=game->hit(p);
            if (b) {showLevelOnScene();}//intersected with item and needed to repaint ui
            if (game->levelFinished()){game->saveProgress(ui->levelProgress_LE->text());ui->stackedWidget->setCurrentIndex(0);}
        }
        return;
    }

    if (ui->stackedWidget->currentIndex()==0){
        qDebug()<<"TO THE GAME";

        ui->stackedWidget->setCurrentIndex(1);
        //load level
        loadLevel();
        showLevelOnScene();
        return;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mMouseDragging = false;

        mLastMouseDragLocation = event->pos();
        setCursor(Qt::CursorShape::ArrowCursor);
    }

    game->changed=true;
    QWidget::update();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"Mouse Move Event"<<event->pos();
    if (mMouseDragging)
    {
        QPoint delta = event->pos() - mLastMouseDragLocation;
        //scroll(delta.x(), delta.y(), rect());
        ui->scrollArea->horizontalScrollBar()->setValue(ui->scrollArea->horizontalScrollBar()->value() - delta.x());
        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() - delta.y());
        mLastMouseDragLocation = event->pos();
    }

}

QPoint Widget::getHitPosition(QMouseEvent *event)
{
    int border=10;//px left and right,top and buttom border

    qDebug()<<"real w:"<<ui->contentLabel->geometry().width()<<"h:"<<ui->contentLabel->geometry().height();
    qDebug()<<"screen w:"<<game->getScreen().getWidth()<<"h:"<<game->getScreen().getHeight();

    QPoint center=ui->contentLabel->geometry().center();
    QPoint fullImg=QPoint(center.x()*2,center.y()*2);
    qDebug()<<"just center"<<center;
    qDebug()<<fullImg;
//    game->level.getBuckground().getSize().height();
    int sub_h=(game->getScreenSize().height()-ui->contentLabel->geometry().height())/2;
    qDebug()<<"SUB"<<sub_h<<"i"<<game->getScreenSize().height()<<"ri"<<ui->contentLabel->height();
//    if (sub_h<0){sub_h=0;}
    QPoint result=QPoint(ui->scrollArea->horizontalScrollBar()->value()+event->pos().x()-border,
                         ui->scrollArea->verticalScrollBar()->value()+event->pos().y()-border+sub_h);
//    qDebug()<<result;
    return result;
}


Widget::~Widget()
{
    delete ui;
}

void Widget::showLevelOnScene()
{
    int pref_w=game->getScreen().getWidth();
    int pref_h=game->getScreen().getHeight();
    GameTask *task=new GameTask();
    task->screenSize=QSize(pref_w,pref_h);
    QPixmap pixmap=*game->getScene(task);

    ui->contentLabel->setPixmap(pixmap);
//    ui->contentLabel->setScaledContents( true );
//    ui->contentLabel->setGeometry(0,0,pref_w,pref_h);

//    qDebug()<<game->getItem0();
    int w=width()/3;
    w=w/2;
    ui->searchedItem0->setPixmap(game->getItem0().scaled(w,w));
    ui->searchedItem1->setPixmap(game->getItem1().scaled(w,w));
    ui->searchedItem2->setPixmap(game->getItem2().scaled(w,w));
}

void Widget::setLevelProgress(QString str)
{
    ui->levelProgress_LE->setText(str);
}


void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::loadLevel()
{
    QMovie *movie = new QMovie(":/img/load.gif");
    loadingLevelProgressLabel->setMovie(movie);
    loadingLevelProgressLabel->setAlignment(Qt::AlignCenter);
    loadingLevelProgressLabel->setVisible(true);
    loadingLevelProgressLabel->setGeometry(0,0,game->getScreen().getWidth(),game->getScreen().getHeight());
//    loadingLevelProgressLabel->setGeometry(0,0,this->width(),this->height());
    movie->start();
    loadingLevelProgressLabel->raise();
    loadingLevelProgressLabel->show();

    game->loadLevel("testLevel");

    loadingLevelProgressLabel->setVisible(false);
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
