#pragma once

#include "NcursesDefenitions.hpp"

struct ConsoleSize
{
    int width = 0;
    int hight = 0;
    ConsoleSize() = default;
    ConsoleSize(int x, int y);
};

class ConsoleDrawer
{
public:
    static ConsoleDrawer& getInstance();

    void start();
    void finish();
    void update();
    void clear();

    CONSOLE_CHARACTER_TYPE getKeyPressed();

    void draw(int x, int y,
              CONSOLE_CHARACTER_TYPE character,
              CharacterAttribute attributes = CharacterAttribute::Normal);

    void draw(int x, int y,
              ConsoleCharacter character = ConsoleCharacter::StripedBlock,
              CharacterAttribute attributes = CharacterAttribute::Normal);

    void drawColored(int x, int y,
                     char character,
                     ConsoleColor color = ConsoleColor::Red,
                     ConsoleColor backgroundColor = ConsoleColor::Black,
                     CharacterAttribute attributes = CharacterAttribute::Normal);

    void drawColored(int x, int y,
                     ConsoleCharacter character = ConsoleCharacter::StripedBlock,
                     ConsoleColor color = ConsoleColor::Red,
                     ConsoleColor backgroundColor = ConsoleColor::Black,
                     CharacterAttribute attributes = CharacterAttribute::Normal);

    ConsoleSize getConsoleSize();

private:
    ConsoleDrawer();
    ~ConsoleDrawer();
};