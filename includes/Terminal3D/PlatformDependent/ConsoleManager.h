#pragma once

#include "Terminal3D/Math.h"

class ConsoleManager
{
public:
	static bool TryToInitializeConsole();
	static bool TryToInitializeConsole(Vector2DI screenSize);

	static void SleepForMilliseconds(size_t duration);

	static void PrintScreenBuffer(const char* screenBuffer, size_t screenBufferSize);

	static Vector2DI GetScreenBufferSize() { return screenBufferSize; }

private:

	static Vector2DI screenBufferSize;
};