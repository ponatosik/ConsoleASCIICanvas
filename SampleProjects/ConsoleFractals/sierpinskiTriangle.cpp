#include <thread>
#include <math.h>
#include <chrono>
#include <time.h>
#include <ConsoleASCIICanvas/ConsoleDrawing.hpp>

#define SIERPINSKI_PRECISON 300000

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
    int width = size.width;

    Point points[] = {{0,float(hight-1)},{float(width*10/17-1),float(hight-1)},{float(width*10/17-1)/2,0}};

    for(int i =0; i < 3; i++)
    {
        drawer.drawColored(points[i].x,points[i].y,'@',ConsoleColor::Red);
    }

    Point triangleGeneartor = points[rand()%3];

    for(int i =0; i < SIERPINSKI_PRECISON; i++)
    {
        Point randomPoint =  points[rand()%3];
        triangleGeneartor.x = (triangleGeneartor.x + randomPoint.x)/2;
        triangleGeneartor.y = (triangleGeneartor.y + randomPoint.y)/2;
        drawer.drawColored(triangleGeneartor.x,triangleGeneartor.y,'@', ConsoleColor::Green);
        drawer.update();
        drawer.draw(triangleGeneartor.x,triangleGeneartor.y,'@');
    }

    drawer.update();
    std::this_thread::sleep_for(std::chrono::seconds(100));

    drawer.finish();

    return 0;
}

