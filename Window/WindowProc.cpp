#include "WindowProc.h"
#include "../Globals/Globals.h"


static void DrawCircle(HDC hdc) {
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Ellipse(hdc,
			circle.x - circleRadius,
			circle.y - circleRadius,
			circle.x + circleRadius,
			circle.y + circleRadius);
}

LRESULT CALLBACK WindowProc::StaticWindowProc(HWND hwnd,
											  UINT message,
											  WPARAM wParam,
											  LPARAM lParam) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	switch (message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			windowRect = {
				0,
				0,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top
			};
			FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + 1));
			DrawCircle(hdc);
			EndPaint(hwnd, &ps);
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WindowProc::MovableWindowProc(HWND hwnd,
											   UINT message,
											   WPARAM wParam,
											   LPARAM lParam) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	switch (message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			windowRect = {
				0,
				0,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top
			};
			FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + 1));
			DrawCircle(hdc);
			EndPaint(hwnd, &ps);
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
