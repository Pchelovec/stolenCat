#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QSize>
class GameTask : public QObject
{
    Q_OBJECT
public:
    explicit GameTask(QObject *parent = nullptr);
    QSize screenSize;

private:
    int default_w=400;
    int default_h=600;
};

#endif // GAMETASK_H
