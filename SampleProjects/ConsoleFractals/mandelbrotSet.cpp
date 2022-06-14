#include <math.h>
#include <ConsoleASCIICanvas/ConsoleDrawing.hpp>

#define MANDELBROT_PRECISON 300

int mandelbrot(long double x, long double y)
{
    long double x0 = x;
    long double y0 = y;
    int i;
    for (i = 0; i < MANDELBROT_PRECISON; i++)
    {
        long double xTemp = x;
        x = x * x - y * y + x0;
        y = 2 * xTemp * y + y0;

        if (x * x + y * y > 4)
            return i;
    }
    return MANDELBROT_PRECISON;
}

int main()
{
    ConsoleDrawer& drawer = ConsoleDrawer::getInstance();
    drawer.start();
    ConsoleSize size = drawer.getConsoleSize();
    int hight = size.hight;
    int width = size.width;

    long double zoom = 0;

    long double xOffset = 2;
    long double yOffset = 2;

    long double speed = 0.5;
    long double zoomSpeed = 0.05;

    char charGradient[] = " .:!/r(l1Z4H9W8$@";
    ConsoleColor colorGradient[] = {ConsoleColor::Green,
                                    ConsoleColor::Cyan,
                                    ConsoleColor::Blue,
                                    ConsoleColor::Magenta,
                                    ConsoleColor::White};

    int charGradientSize = sizeof(charGradient) / sizeof(char) - 2;
    int colorGradientSize = sizeof(colorGradient) / sizeof(ConsoleColor) - 1;

    char consoleInput;

    while (true)
    {
        consoleInput = drawer.getKeyPressed();

        switch (consoleInput)
        {
        case 'q':
            zoom += (zoomSpeed) * (1 - zoom);
            break;
        case 'e':
            zoom -= (zoomSpeed) * (1 - zoom) + 0.000000000001;
            break;
        case 'w':
            yOffset += speed * (1 - zoom);
            break;
        case 'a':
            xOffset += speed * (1 - zoom);
            break;
        case 's':
            yOffset -= speed * (1 - zoom);
            break;
        case 'd':
            xOffset -= speed * (1 - zoom);
            break;
        }

        for (int i = 0; i < hight; i++)
            for (int j = 0; j < width; j++)
            {
                int m = mandelbrot(((long double)j * 4 * (1 - zoom)) / width - xOffset + zoom * 2, ((long double)i * 4 * (1 - zoom)) / hight - yOffset + zoom * 2);

                if (m == MANDELBROT_PRECISON)
                {
                    drawer.draw(j, i, ConsoleCharacter::StripedBlock);
                }
                else
                {
                    char character = charGradient[(int)floor((float)charGradientSize * m / MANDELBROT_PRECISON)];
                    ConsoleColor color = colorGradient[(int)floor((float)colorGradientSize * m / MANDELBROT_PRECISON)];
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
