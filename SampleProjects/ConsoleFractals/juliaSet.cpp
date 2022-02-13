#include <math.h>
#include <ConsoleASCIICanvas/ConsoleDrawing.hpp>

#define JULIA_PRECISON 100

double julia(double x, double y, double x0, double y0)
{
    int i;
    for (i = 0; i < JULIA_PRECISON; i++)
    {
        double xTemp = x;
        x = x * x - y * y + x0;
        y = 2 * xTemp * y + y0;

        if (x * x + y * y > 4)
            return i;
    }
    return JULIA_PRECISON;
}

int main()
{
    ConsoleDrawer drawer;
    drawer.start();
    ConsoleSize size = drawer.getConsoleSize();
    int hight = size.hight;
    int width = size.width;

    double zoom = 0.5;

    double zoomSpeeed = 0.00001;

    double xOffset = 2;
    double yOffset = 2;

    char charGradient[] = " .:!/r(l1Z4H9W8$@";
    ConsoleColor colorGradient[] = {ConsoleColor::Green,
                                    ConsoleColor::Cyan,
                                    ConsoleColor::Blue,
                                    ConsoleColor::Magenta,
                                    ConsoleColor::White};

    int charGradientSize = sizeof(charGradient) / sizeof(char) - 2;
    int colorGradientSize = sizeof(colorGradient) / sizeof(ConsoleColor) - 1;

    double x0 = 0.5;
    double y0 = 0.3;

    double xSpeed = -0.0001;
    double ySpeed = 0.00005;

    while (true)
    {
        zoom += zoomSpeeed;
        x0 += xSpeed;
        y0 += ySpeed;

        for (int i = 0; i < hight; i++)
            for (int j = 0; j < width; j++)
            {
                int m = julia(((double)j * 4 * (1 - zoom)) / width - xOffset + zoom * 2, ((double)i * 4 * (1 - zoom)) / hight - yOffset + zoom * 2, x0, y0);

                if (m == JULIA_PRECISON)
                {
                    drawer.drawColored(j, i, '@', ConsoleColor::Red);
                }
                else
                {
                    char character = charGradient[(int)floor((float)charGradientSize * m / JULIA_PRECISON)];
                    ConsoleColor color = colorGradient[(int)floor((float)colorGradientSize * m / JULIA_PRECISON)];
                    drawer.drawColored(j, i, character, color);
                }
            }
        drawer.update();

        size = drawer.getConsoleSize();
        hight = size.hight;
        width = size.width;
    }
    drawer.finish();
    return 0;
}
