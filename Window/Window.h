#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#include "../Globals/Globals.h"


struct WindowShape {
	uint16_t height;
	uint16_t width;
};


static bool IsPointInWindow(HWND hwnd)
{
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	std::cout << circle.x - circleRadius << ' ' << circle.y - circleRadius << ' ' <<
			  circle.x + circleRadius << ' ' << circle.y + circleRadius << '\n';
	std::cout << windowRect.left << ' ' << windowRect.top << ' ' << windowRect.right
			  << ' ' << windowRect.bottom << "\n\n";
	return circle.x - circleRadius >= 0 && circle.x + circleRadius <= winSize &&
		   circle.y - circleRadius >= 0 && circle.y + circleRadius <= winSize;
}


class Window {
private:
	WindowShape shape;
	HWND hwnd;

public:
	Window(const std::string& ClassName,
		const std::string& WindowName,
		WindowShape shape,
		POINT position);

	HWND Create(
		const std::string& ClassName,
		const std::string& WindowName,
		WindowShape shape,
		POINT position) const;

	HWND getHwnd() {
		return this->hwnd;
	}
};


#endif // WINDOW_H