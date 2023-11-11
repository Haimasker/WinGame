#include "WindowProc.h"
#include "../Globals/Globals.h"


static void DrawCircle(HDC hdc, HWND hwnd)
{
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));

	Ellipse(hdc,
		(circle.x - circleRadius),
		(circle.y - circleRadius),
		(circle.x + circleRadius),
		(circle.y + circleRadius));
}


LRESULT CALLBACK WindowProc::StaticWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + 1));
		DrawCircle(hdc, hwnd);
		ValidateRect(hwnd, NULL);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_MOVE: {
		InvalidateRect(hwnd, &windowRect, true);
		break;
	}

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}


LRESULT CALLBACK WindowProc::MovableWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + 1));
		DrawCircle(hdc, hwnd);
		ValidateRect(hwnd, NULL);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_MOVE: {
		InvalidateRect(hwnd, &windowRect, true);
		break;
	}

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}