#include "WindowProc.h"
#include "../Globals/Globals.h"
#include <iostream>


static void DrawCircle(const HDC& hdc, const HWND& hwnd) {
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));

	POINT relativeCircle = circle;
	ScreenToClient(hwnd, &relativeCircle);

	Ellipse(hdc,
			relativeCircle.x - circleRadius,
			relativeCircle.y - circleRadius,
			relativeCircle.x + circleRadius,
			relativeCircle.y + circleRadius);
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
			RECT windowShape = {
				0,
				0,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top
			};
			FillRect(hdc, &windowShape, (HBRUSH)(COLOR_WINDOW + 1));
			DrawCircle(hdc, hwnd);
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
			RECT windowShape = {
				0,
				0,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top
			};
			FillRect(hdc, &windowShape, (HBRUSH)(COLOR_WINDOW + 1));
			DrawCircle(hdc, hwnd);
			EndPaint(hwnd, &ps);
			break;
		}

		case WM_MOVE: {
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
