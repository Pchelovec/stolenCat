#ifndef SCREEN_H
#define SCREEN_H


class Screen
{
public:
    Screen();

    int getHeight(){return height;}
    int getWidth(){return width;}
private:
    int height;
    int width;
};

#endif // SCREEN_H
