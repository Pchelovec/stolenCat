#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
#include <QScreen>
#include <QDebug>

#include <QTouchEvent>
#include<QScrollBar>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    game=new Game();
    loadWalkedCat();
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::loadWalkedCat()
{
    QMovie *movie = new QMovie(":/img/cat0.gif");
    movie->setScaledSize(QSize(600,400));
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    ui->label->setToolTip("This cat was stolen");
    movie->start();
}

bool Widget::checkIsInContentArea(QPoint pos)
{
//    qDebug()<<"scrollAreaPosition:"<<pos;
//    qDebug()<<"geometry:"<<ui->scrollArea->horizontalScrollBar()->value()<< " "<<ui->scrollArea->verticalScrollBar()->value();
//    qDebug()<<"content:"<<ui->contentLabel->geometry().width()<<" "<<ui->contentLabel->geometry().height();
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

    //HIT
    QPoint p=getHitPosition(event);
//    QPoint widgetPosition=event->pos();
    if (checkIsInContentArea(p)){
        game->hit(p);
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

    QPoint result=QPoint(ui->scrollArea->horizontalScrollBar()->value()+event->pos().x()-border,
                         ui->scrollArea->verticalScrollBar()->value()+event->pos().y()-border);
//    qDebug()<<result;
    return result;
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //set ui page
    ui->stackedWidget->setCurrentIndex(1);

    //load level
    game->loadLevel("testLevel");

    GameTask *task=new GameTask();
    task->screenSize=QSize(game->getScreen().getWidth(),game->getScreen().getHeight());
    QPixmap pixmap=*game->getScene(task);

    ui->contentLabel->setPixmap(pixmap);
    ui->contentLabel->setScaledContents( true );

//    qDebug()<<game->getItem0();
    ui->searchedItem0->setPixmap(game->getItem0().scaled(120,100));
    ui->searchedItem1->setPixmap(game->getItem1().scaled(120,100));
    ui->searchedItem2->setPixmap(game->getItem2().scaled(120,100));
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
