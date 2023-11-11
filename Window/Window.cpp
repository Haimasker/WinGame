#include "Window.h"


Window::Window(const std::string& className,
	const std::string& windowName,
	WindowShape shape,
	POINT position)
{
	this->shape = shape;
	this->hwnd = this->Create(className, windowName, shape, position);
	windowList.push_back(this);
}


HWND Window::Create(const std::string& ClassName,
	const std::string& WindowName,
	WindowShape shape,
	POINT position) const
{
	HWND hwnd = CreateWindowExA(DWORD(0),
		ClassName.c_str(),
		WindowName.c_str(),
		windowStyles[ClassName.c_str()],
		position.x,
		position.y,
		shape.width,
		shape.height,
		nullptr,
		nullptr,
		GetModuleHandleA(0),
		nullptr);
	ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}