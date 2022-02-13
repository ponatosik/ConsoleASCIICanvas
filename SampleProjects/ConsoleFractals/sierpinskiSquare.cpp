#include <thread>
#include <math.h>
#include <chrono>
#include <time.h>
#include <ConsoleASCIICanvas/ConsoleDrawing.hpp>

#define SIERPINSKI_PRECISON 3000000

struct Point
{
    float x,y;
};

int main()
{
    srand(time(NULL));
    ConsoleDrawer drawer;
    drawer.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    drawer.update();
    ConsoleSize size = drawer.getConsoleSize();
    int hight = size.hight;
    int width = size.width *10/17;

    Point attractionPoints[] = {
        {0,0},
        {0,(float)hight},
        {(float)width,0},
        {(float)width,(float)hight},

        {(float)width/2,0},
        {(float)width/2,(float)hight},
        {0,(float)hight/2},
        {(float)width,(float)hight/2}
    };

    for(int i =0; i < 8; i++)
    {
        drawer.drawColored(attractionPoints[i].x,attractionPoints[i].y,'@',ConsoleColor::Red);
    }
        drawer.update();

    Point squarGeneartor = attractionPoints[rand()%8];

    for(int i =0; i < SIERPINSKI_PRECISON; i++)
    {
        Point randomPoint =  attractionPoints[rand()%8];
        squarGeneartor.x = (squarGeneartor.x + randomPoint.x*2)/3;
        squarGeneartor.y = (squarGeneartor.y + randomPoint.y*2)/3;
        drawer.draw(squarGeneartor.x,squarGeneartor.y,' ',CharacterAttribute::ReverseColors);
        drawer.update();
    }

    drawer.update();
    std::this_thread::sleep_for(std::chrono::seconds(100));

    drawer.finish();

    return 0;
}

