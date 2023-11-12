#include "Window.h"


Window::Window(const std::string& className,
			   const std::string& windowName,
			   WindowShape shape,
			   POINT position) {
	this->shape = shape;
	this->hwnd = Window::create(className, windowName, shape, position);
	windowList.push_back(this);
}

HWND Window::create(const std::string& ClassName,
					const std::string& WindowName,
					WindowShape shape,
					POINT position) {
	HWND hwnd = CreateWindowExA(DWORD(0),
								ClassName.c_str(),
								WindowName.c_str(),
								windowStyles[ClassName.c_str()],
								position.x,
								position.y,
								shape.width,
								shape.height,
								NULL,
								NULL,
								GetModuleHandleA(0),
								nullptr);
	ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}

WindowShape Window::getShape() const {
	return this->shape;
}

HWND Window::getHwnd() const {
	return this->hwnd;
}
