#ifndef WINDOW_PROC_H
#define WINDOW_PROC_H

#include <Windows.h>


class WindowProc {
public:
	static LRESULT CALLBACK StaticWindowProc(HWND hwnd,
											 UINT message,
											 WPARAM wParam,
											 LPARAM lParam);

	static LRESULT CALLBACK MovableWindowProc(HWND hwnd,
											  UINT message,
											  WPARAM wParam,
											  LPARAM lParam);
};


#endif // WINDOW_PROC_H
