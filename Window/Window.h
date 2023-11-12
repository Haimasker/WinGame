#ifndef WINDOW_H
#define WINDOW_H

#include "../Globals/Globals.h"


struct WindowShape {
	int16_t height;
	int16_t width;
};

class Window {
private:
	WindowShape shape;
	HWND hwnd;

	static HWND create(const std::string& ClassName,
					   const std::string& WindowName,
					   WindowShape shape,
					   POINT position);
public:
	Window(const std::string& ClassName,
		   const std::string& WindowName,
		   WindowShape shape,
		   POINT position);

	WindowShape getShape() const;
	HWND getHwnd() const;
};


#endif // WINDOW_H
