#pragma once
#include <Windows.h>

namespace console {
	class parameters {
	public:

        static void set_color(const int text, const int background);

        static void set_position(const int x, const int y);

    private:
        static HANDLE hConsole;
	};
}