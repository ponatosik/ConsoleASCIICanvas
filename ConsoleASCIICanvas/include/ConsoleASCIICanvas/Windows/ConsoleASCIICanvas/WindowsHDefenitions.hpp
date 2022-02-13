#pragma once

#include <Windows.h>

#define CONSOLE_CHARACTER_TYPE wchar_t
#define CONSOLE_ATTRIBUTE_TYPE WORD
#define CONSOLE_COLOR_TYPE short
#define NUMBER_OF_DEFINED_COLORS 8

enum class ConsoleCharacter : CONSOLE_CHARACTER_TYPE
{
    StripedBlock = 0x2593,
    Diamond = 0x2666,
    UpperLeftCorner = 0x2519,
    LowerLeftCorner = 0x2514,
    UpperRightCorner = 0x2510,
    LowerRightCorner = 0x2518,
    TPointingRight = 0x251C,
    TPointingLeft = 0x2524,
    TPointingUp = 0x2534,
    TPointingDown = 0x252C,
    HorizontalLine = 0x2500,
    Cross = 0x253C,
    VerticalLine = 0x2502,
    LineCrossOver = 0x2501,
    Degree = 0x00BA,
    PlusMinus = 0x00B1,
    Bullet = 0x2219,
    LessEqual = 0x2264,
    GreaterEqual = 0x2265,
    Pi = 0x03C0,
    NotEqual = 0x2262,
    Pound = 0x00A3,
};

enum class CharacterAttribute : CONSOLE_ATTRIBUTE_TYPE
{
    Normal = 0,
    ReverseColors = COMMON_LVB_REVERSE_VIDEO,
    Underline = COMMON_LVB_UNDERSCORE,
};

CharacterAttribute operator+(CharacterAttribute attr1, CharacterAttribute attr2);

enum class ConsoleColor : CONSOLE_COLOR_TYPE
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
};
