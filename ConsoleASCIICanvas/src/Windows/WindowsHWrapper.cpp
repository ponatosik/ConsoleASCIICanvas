#include <stdio.h>
#include <iostream>
#include "ConsoleDrawing.hpp"

#include <map>


CharacterAttribute operator + (CharacterAttribute attr1, CharacterAttribute attr2)
{
	return CharacterAttribute((CONSOLE_ATTRIBUTE_TYPE)attr1 + (CONSOLE_ATTRIBUTE_TYPE)attr2);
}

const static std::map<ConsoleColor, CONSOLE_COLOR_TYPE> foregroundColors =
{
	{ConsoleColor::White, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN},
	{ConsoleColor::Cyan, FOREGROUND_BLUE | FOREGROUND_GREEN},
	{ConsoleColor::Magenta, FOREGROUND_BLUE | FOREGROUND_RED},
	{ConsoleColor::Yellow, FOREGROUND_RED | FOREGROUND_GREEN},
	{ConsoleColor::Blue, FOREGROUND_BLUE},
	{ConsoleColor::Red, FOREGROUND_RED},
	{ConsoleColor::Green, FOREGROUND_GREEN},
	{ConsoleColor::Black, 0}
};

const static std::map<ConsoleColor, CONSOLE_COLOR_TYPE> backgroundColors =
{
	{ConsoleColor::White, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN},
	{ConsoleColor::Cyan, BACKGROUND_BLUE | BACKGROUND_GREEN},
	{ConsoleColor::Magenta, BACKGROUND_BLUE | BACKGROUND_RED },
	{ConsoleColor::Yellow, BACKGROUND_RED | BACKGROUND_GREEN},
	{ConsoleColor::Blue, BACKGROUND_BLUE},
	{ConsoleColor::Red, BACKGROUND_RED},
	{ConsoleColor::Green, BACKGROUND_GREEN},
	{ConsoleColor::Black, 0}
};

ConsoleDrawer::ConsoleDrawer()
{	
	_consoleHandler = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	ConsoleSize console = getConsoleSize();
	_screenBuffer = new CHAR_INFO[CONSOLE_BUFFER_SIZE];
	_windowsRect = { 0,0, short(console.width - 1), short(console.hight - 1) };
	_windowsSize = { _windowsRect.Right - _windowsRect.Left + 1, _windowsRect.Bottom - _windowsRect.Top + 1 };

	CHAR_INFO defaultChar;
	defaultChar.Char.UnicodeChar = L' ';
	defaultChar.Attributes = foregroundColors.at(ConsoleColor::White) | backgroundColors.at(ConsoleColor::Black);
	for (int i = 0; i < CONSOLE_BUFFER_SIZE; i++)_screenBuffer[i] = defaultChar;
}

void ConsoleDrawer::start() 
{
	resizeBuffer();
	SetConsoleActiveScreenBuffer(_consoleHandler);
	SetConsoleScreenBufferSize(_consoleHandler, { short(_windowsSize.width)  , short(_windowsSize.hight) });
	clear();
}

void ConsoleDrawer::clear()
{
	for (int x = 0; x < _windowsSize.width; x++)
	{
		for (int y = 0; y < _windowsSize.hight; y++)
		{
			drawColored(x, y, L' ', ConsoleColor::White);
		}
	}
}

void ConsoleDrawer::update()
{
	ConsoleSize currentSize = getConsoleSize();
	if (currentSize.width != _windowsSize.width || currentSize.hight != _windowsSize.hight)
		resizeBuffer();
	WriteConsoleOutput(_consoleHandler, _screenBuffer, { short(_windowsSize.width) , short(_windowsSize.hight) }, { 0,0 }, &_windowsRect);
}

ConsoleDrawer::~ConsoleDrawer()
{
	finish();
	delete[] _screenBuffer;
}

void ConsoleDrawer::finish()
{
	clear();
	update();
}

void ConsoleDrawer::draw(int x, int y, CONSOLE_CHARACTER_TYPE character, CharacterAttribute attribute)
{
	_screenBuffer[y * _windowsSize.width + x].Char.UnicodeChar = character;
	_screenBuffer[y * _windowsSize.width + x].Attributes = (CONSOLE_ATTRIBUTE_TYPE)attribute + foregroundColors.at(ConsoleColor::White);
}
void ConsoleDrawer::draw(int x, int y, ConsoleCharacter character, CharacterAttribute attribute )
{
	_screenBuffer[y * _windowsSize.width + x].Char.UnicodeChar = (CONSOLE_CHARACTER_TYPE)character;
	_screenBuffer[y * _windowsSize.width + x].Attributes = (CONSOLE_ATTRIBUTE_TYPE)attribute + foregroundColors.at(ConsoleColor::White);
}
void ConsoleDrawer::drawColored(int x, int y, CONSOLE_CHARACTER_TYPE character, ConsoleColor color, ConsoleColor backgroundColor, CharacterAttribute attribute)
{
	_screenBuffer[y * _windowsSize.width + x].Char.UnicodeChar = (CONSOLE_CHARACTER_TYPE)character;
	CONSOLE_COLOR_TYPE colorAttr = foregroundColors.at(color) | backgroundColors.at(backgroundColor);
	_screenBuffer[y * _windowsSize.width + x].Attributes = colorAttr + (CONSOLE_ATTRIBUTE_TYPE)attribute;
}
void ConsoleDrawer::drawColored(int x, int y, ConsoleCharacter character, ConsoleColor color, ConsoleColor backgroundColor, CharacterAttribute attribute)
{
	_screenBuffer[y * _windowsSize.width + x].Char.UnicodeChar = (CONSOLE_CHARACTER_TYPE)character;
	CONSOLE_COLOR_TYPE colorAttr = foregroundColors.at(color) | backgroundColors.at(backgroundColor);
	_screenBuffer[y * _windowsSize.width + x].Attributes = colorAttr + (CONSOLE_ATTRIBUTE_TYPE)attribute;
}

ConsoleSize ConsoleDrawer::getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
	GetConsoleScreenBufferInfo(_consoleHandler, &ScreenBufferInfo);

	int width = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
	int hight = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
	return ConsoleSize(width,hight);
}
void ConsoleDrawer::resizeBuffer() 
{
	ConsoleSize consoleSize = getConsoleSize();

	_windowsRect = { 0,0, short(consoleSize.width - 1), short(consoleSize.hight - 1) };
	_windowsSize = { _windowsRect.Right - _windowsRect.Left + 1, _windowsRect.Bottom - _windowsRect.Top + 1 };
}

ConsoleSize::ConsoleSize(int x, int y)
{
	width = x;
	hight = y;
}