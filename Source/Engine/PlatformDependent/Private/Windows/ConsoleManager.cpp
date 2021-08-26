#include "ConsoleManager.h"

#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Vector2DI ConsoleManager::screenBufferSize;

namespace
{
	void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}
}

bool ConsoleManager::TryToInitializeConsole()
{
	return TryToInitializeConsole({ 1280, 720 });
}

bool ConsoleManager::TryToInitializeConsole(Vector2DI screenSize)
{
	system("cls");

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, screenSize.x, screenSize.y, TRUE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	screenBufferSize.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	screenBufferSize.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	ShowConsoleCursor(false);

	return true;
}

void ConsoleManager::SleepForMilliseconds(size_t duration)
{
	Sleep(static_cast<DWORD>(duration));
}

void ConsoleManager::PrintScreenBuffer(const char* screenBuffer, size_t screenBufferSize)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, { 0, 0 });

	fwrite(screenBuffer, sizeof(char), screenBufferSize, stdout);
}
