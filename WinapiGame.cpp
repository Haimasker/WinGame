#include <Windows.h>
#include "Globals/Globals.h"
#include "Window/WindowProc.h"
#include "Window/Window.h"

void RegisterStaticWindowClass(const std::string& ClassName) {
	WNDCLASSEXA wc = {};
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpfnWndProc = WindowProc::StaticWindowProc;
	wc.hInstance = GetModuleHandleA(0);
	wc.lpszClassName = ClassName.c_str();
	RegisterClassExA(&wc);
}

void RegisterMovableWindowClass(const std::string& ClassName) {
	WNDCLASSEXA wc = {};
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpfnWndProc = WindowProc::MovableWindowProc;
	wc.hInstance = GetModuleHandleA(0);
	wc.lpszClassName = ClassName.c_str();
	RegisterClassExA(&wc);
}

void RepaintAllWindows() {
	for (auto& window : windowList)
		InvalidateRect(window->getHwnd(), NULL, TRUE);
}

int main() {
	for (auto& window : windowList) {
		std::cout << window->getHwnd() << "!\n";
	}

	RegisterStaticWindowClass("StaticWindow");
	Window staticWin = Window("StaticWindow",
		"1",
		WindowShape{ winSize, winSize },
		POINT{ 0, 0 });

	RegisterStaticWindowClass("MovableWindow");
	Window movableWin = Window("MovableWindow",
		"2",
		WindowShape{ winSize, winSize },
		POINT{ long(1.5 * winSize), 0 });

	MSG msg { 0 };
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_KEYDOWN) {
			switch (msg.wParam) {
			case 'W':
				circle.y -= step;
				break;
			case 'A':
				circle.x -= step;
				break;
			case 'S':
				circle.y += step;
				break;
			case 'D':
				circle.x += step;
				break;
			}
			RepaintAllWindows();
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

