#include <iostream>

#include <Windows.h>

#include "console.h"

void console::parameters::set_color(const int text, const int background) {
    SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));
}

void console::parameters::set_position(const int x, const int y) {
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition(hConsole, point);
}

HANDLE console::parameters::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);