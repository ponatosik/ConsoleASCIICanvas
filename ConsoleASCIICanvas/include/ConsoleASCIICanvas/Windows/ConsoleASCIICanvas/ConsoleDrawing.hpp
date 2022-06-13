#pragma once
#include <iostream>
#include "WindowsHDefenitions.hpp"

#define CONSOLE_BUFFER_SIZE 256 * 256

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
	ConsoleDrawer();
	void update();
	~ConsoleDrawer();
	void clear();
	void start();
	void finish();

	CONSOLE_CHARACTER_TYPE getKeyPressed();

	void draw(int x, int y,
			  CONSOLE_CHARACTER_TYPE character,
			  CharacterAttribute attribute = CharacterAttribute::Normal);
	void draw(int x, int y,
			  ConsoleCharacter character = ConsoleCharacter::StripedBlock,
			  CharacterAttribute attribute = CharacterAttribute::Normal);

	void drawColored(int x, int y,
					 CONSOLE_CHARACTER_TYPE character,
					 ConsoleColor color = ConsoleColor::Red,
					 ConsoleColor backgroundColor = ConsoleColor::Black,
					 CharacterAttribute attribute = CharacterAttribute::Normal);
	void drawColored(int x, int y,
					 ConsoleCharacter character = ConsoleCharacter::StripedBlock,
					 ConsoleColor color = ConsoleColor::Red,
					 ConsoleColor backgroundColor = ConsoleColor::Black,
					 CharacterAttribute attribute = CharacterAttribute::Normal);

	ConsoleSize getConsoleSize();

private:
	void resizeBuffer();
	ConsoleSize _windowsSize;
	CHAR_INFO *_screenBuffer;
	SMALL_RECT _windowsRect;
	HANDLE _consoleHandler;
	DWORD _consoleMode;
};
