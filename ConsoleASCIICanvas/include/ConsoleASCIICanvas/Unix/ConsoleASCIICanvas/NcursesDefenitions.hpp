#pragma once

#include <ncurses.h>

#define CONSOLE_CHARACTER_TYPE chtype
#define CONSOLE_ATTRIBUTE_TYPE chtype
#define CONSOLE_COLOR_TYPE short
#define NUMBER_OF_DEFINED_COLORS 8

enum class ConsoleCharacter : CONSOLE_CHARACTER_TYPE
{
    Diamond = 96,
    StripedBlock = 97,
    Degree = 102,
    PlusMinus = 103,
    LowerRightCorner = 106,
    UpperRightCorner = 107,
    UpperLeftCorner = 108,
    LowerLeftCorner = 109,
    Cross = 110,
    HorizontalLine = 113,
    TPointingRight = 116,
    TPointingLeft = 117,
    TPointingUp = 118,
    TPointingDown = 119,
    VerticalLine = 120,
    LessEqual = 121,
    GreaterEqual = 122,
    Pi = 123,
    Pound = 125,
    Bullet = 126,
};

enum class CharacterAttribute : CONSOLE_ATTRIBUTE_TYPE
{
    Normal = A_NORMAL,
    ReverseColors = A_STANDOUT,
    Underline = A_UNDERLINE,

//    Reversed = A_REVERSE,
//    Blinking = A_BLINK,
//    HalfBright = A_DIM,
//    Bold = A_BOLD, // HalfHalfBright
//    Protected = A_PROTECT,
//    Invisible = A_INVIS,
//    Alternative = A_ALTCHARSET,

};

CharacterAttribute operator + (CharacterAttribute attr1, CharacterAttribute attr2);

enum class ConsoleColor : CONSOLE_COLOR_TYPE
{
    Black = COLOR_BLACK,
    Red = COLOR_RED,
    Green = COLOR_GREEN,
    Yellow = COLOR_YELLOW,
    Blue = COLOR_BLUE,
    Magenta = COLOR_MAGENTA,
    Cyan = COLOR_CYAN,
    White = COLOR_WHITE,
};