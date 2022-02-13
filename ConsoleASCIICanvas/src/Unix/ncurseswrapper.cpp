#include <ncurses.h>
#include "ConsoleDrawing.hpp"

CharacterAttribute operator+(CharacterAttribute attr1, CharacterAttribute attr2)
{
    return CharacterAttribute((CONSOLE_ATTRIBUTE_TYPE)attr1 | (CONSOLE_ATTRIBUTE_TYPE)attr2);
}

struct ColorPair
{
    CONSOLE_COLOR_TYPE foreground = (CONSOLE_COLOR_TYPE)ConsoleColor::White;
    CONSOLE_COLOR_TYPE background = (CONSOLE_COLOR_TYPE)ConsoleColor::Black;
    ColorPair(CONSOLE_COLOR_TYPE foreground, CONSOLE_COLOR_TYPE background)
    {
        this->foreground = foreground;
        this->background = background;
    }
    ColorPair()
    {
        foreground = (CONSOLE_COLOR_TYPE)ConsoleColor::White;
        background = (CONSOLE_COLOR_TYPE)ConsoleColor::Black;
    }
};

void initializePairs()
{
    for (ConsoleColor i = ConsoleColor::Black; i <= ConsoleColor::White; i = ConsoleColor((CONSOLE_COLOR_TYPE)i + 1))
        for (ConsoleColor j = ConsoleColor::Black; j <= ConsoleColor::White; j = ConsoleColor((CONSOLE_COLOR_TYPE)j + 1))
        {
            init_pair(((CONSOLE_COLOR_TYPE)i * NUMBER_OF_DEFINED_COLORS + (CONSOLE_COLOR_TYPE)j) + 1, (CONSOLE_COLOR_TYPE)i, (CONSOLE_COLOR_TYPE)j);
        }
}

ConsoleDrawer::ConsoleDrawer()
{
}
ConsoleDrawer::~ConsoleDrawer()
{
    finish();
}

void ConsoleDrawer::start()
{
    initscr();

    start_color();
    initializePairs();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
}
void ConsoleDrawer::finish()
{
    endwin();
}
void ConsoleDrawer::update()
{
    refresh();
}
void ConsoleDrawer::clear()
{
    erase();
}
void ConsoleDrawer::draw(int x, int y, ConsoleCharacter character, CharacterAttribute attributes)
{
    CONSOLE_CHARACTER_TYPE _character = NCURSES_ACS((CONSOLE_CHARACTER_TYPE)character);
    mvaddch(y, x, _character | (CONSOLE_ATTRIBUTE_TYPE)attributes);
}
void ConsoleDrawer::draw(int x, int y, CONSOLE_CHARACTER_TYPE character, CharacterAttribute attributes)
{
    mvaddch(y, x, (CONSOLE_CHARACTER_TYPE)character | (CONSOLE_ATTRIBUTE_TYPE)attributes);
}
void ConsoleDrawer::drawColored(int x, int y, char character, ConsoleColor color, ConsoleColor backgroundColor, CharacterAttribute attributes)
{
    int colorPaiarId = ((CONSOLE_COLOR_TYPE)color * NUMBER_OF_DEFINED_COLORS + (CONSOLE_COLOR_TYPE)backgroundColor) + 1;
    mvaddch(y, x, (CONSOLE_CHARACTER_TYPE)character | (CONSOLE_ATTRIBUTE_TYPE)attributes | COLOR_PAIR(colorPaiarId));
}
void ConsoleDrawer::drawColored(int x, int y, ConsoleCharacter character, ConsoleColor color, ConsoleColor backgroundColor, CharacterAttribute attributes)
{
    CONSOLE_CHARACTER_TYPE _character = NCURSES_ACS(character);
    int colorPaiarId = ((CONSOLE_COLOR_TYPE)color * NUMBER_OF_DEFINED_COLORS + (CONSOLE_COLOR_TYPE)backgroundColor) + 1;
    mvaddch(y, x, (CONSOLE_CHARACTER_TYPE)_character | (CONSOLE_ATTRIBUTE_TYPE)attributes | COLOR_PAIR(colorPaiarId));
}

ConsoleSize ConsoleDrawer::getConsoleSize()
{
    int x;
    int y;
    getmaxyx(stdscr, y, x);
    return ConsoleSize(x, y);
}

ConsoleSize::ConsoleSize(int x, int y)
{
    width = x;
    hight = y;
}