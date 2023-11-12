#include "Window/WindowProc.h"
#include "Window/Window.h"


static void RegisterStaticWindowClass(const std::string& ClassName) {
	WNDCLASSEXA wc = {};
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpfnWndProc = WindowProc::StaticWindowProc;
	wc.hInstance = GetModuleHandleA(0);
	wc.lpszClassName = ClassName.c_str();
	RegisterClassExA(&wc);
}

static void RegisterMovableWindowClass(const std::string& ClassName) {
	WNDCLASSEXA wc = {};
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpfnWndProc = WindowProc::MovableWindowProc;
	wc.hInstance = GetModuleHandleA(0);
	wc.lpszClassName = ClassName.c_str();
	RegisterClassExA(&wc);
}

static bool IsPointInWindow(POINT& point, HWND hwnd) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	bool pointInWindow = point.x >= windowRect.left &&
						 point.x <= windowRect.right &&
						 point.y >= windowRect.top &&
						 point.y <= windowRect.bottom;

	return pointInWindow;
}

static bool IsCircleInWindow(HWND hwnd) {
	POINT leftTop = { circle.x - circleRadius, circle.y - circleRadius };
	POINT rightTop = { circle.x + circleRadius, circle.y - circleRadius };
	POINT rightBot = { circle.x + circleRadius, circle.y + circleRadius };
	POINT leftBot = { circle.x - circleRadius, circle.y + circleRadius };

	bool circleInWindow = IsPointInWindow(leftTop, hwnd) ||
						  IsPointInWindow(rightTop, hwnd) ||
						  IsPointInWindow(rightBot, hwnd) ||
						  IsPointInWindow(leftBot, hwnd);
	return circleInWindow;
}

void RepaintAllWindows() {
	for (auto& window : windowList)
		if (IsCircleInWindow(window->getHwnd()))
			InvalidateRect(window->getHwnd(), NULL, TRUE);
}

int main() {
	for (auto& window : windowList)
		std::cout << window->getHwnd() << "!\n";

	RegisterStaticWindowClass("StaticWindow");

	Window staticWin1 = Window("StaticWindow",
							   "1",
							   WindowShape{ winSize, winSize },
							   POINT{ 0, 0 });

	Window staticWin2 = Window("StaticWindow",
							   "2",
							   WindowShape{ winSize, winSize },
							   POINT{ long(1.1 * winSize), 0 });

	Window staticWin3 = Window("StaticWindow",
							   "3",
							   WindowShape{ winSize, winSize },
							   POINT{ 0, long(1.1 * winSize) });

	Window staticWin4 = Window("StaticWindow",
							   "4",
							   WindowShape{ winSize, winSize },
							   POINT{ long(1.1 * winSize), long(1.1 * winSize) });

	RegisterMovableWindowClass("MovableWindow");
	Window movableWin1 = Window("MovableWindow",
								"5",
								WindowShape{ winSize, winSize },
								POINT{ long(2.2 * winSize), 0 });

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
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}
