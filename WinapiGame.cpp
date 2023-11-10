#include <iostream>
#include <Windows.h>
#include <vector>


struct Circle {
    int x;
    int y;
};


std::vector<HWND> hwndList;
int winSize = 240;
Circle circle{ 0.5 * winSize, 0.5 * winSize };
int circleRadius = 0.2 * winSize;


void DrawCircle(HDC hdc, HWND hwnd) {
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    
    //Ellipse(hdc, (circle.x - circleRadius) - windowRect.left, (circle.y - circleRadius) - windowRect.top, (circle.x + circleRadius) - windowRect.left, (circle.y + circleRadius) - windowRect.top);
    Ellipse(hdc, (circle.x - circleRadius), (circle.y - circleRadius), (circle.x + circleRadius), (circle.y + circleRadius));
}


bool IsPointInWindow(HWND hwnd) {
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    std::cout << circle.x - circleRadius << ' ' << circle.y - circleRadius << ' ' << circle.x + circleRadius << ' ' << circle.y + circleRadius << '\n';
    std::cout << windowRect.left << ' ' << windowRect.top << ' ' << windowRect.right << ' ' << windowRect.bottom << "\n\n";
    return circle.x - circleRadius >= 0 && circle.x + circleRadius <= winSize && circle.y - circleRadius >= 0 && circle.y + circleRadius <= winSize;
}


void RepaintAllWindows() {
    for (auto& hwnd : hwndList) {
        //if (!IsPointInWindow(hwnd))
        //    continue;
        RECT windowRect;
        GetWindowRect(hwnd, &windowRect);
        InvalidateRect(hwnd, &windowRect, true);
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    RECT windowRect;
    

    switch (uMsg) {
    case WM_PAINT: {
        //if (IsPointInWindow(hwnd)) {
            GetWindowRect(hwnd, &windowRect);
            std::cout << "POINT IN WINDOW: " << hwnd << '\n';
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + 1));
            DrawCircle(hdc, hwnd);
            ValidateRect(hwnd, NULL);
            EndPaint(hwnd, &ps);
        //}
        break;
    }
    case WM_MOVE: {
        //RepaintAllWindows();
        GetWindowRect(hwnd, &windowRect);
        InvalidateRect(hwnd, &windowRect, true);

        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int main() {
    const wchar_t* windowClass = L"MyWindowClass";

    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = windowClass;
    RegisterClass(&wc);

    // Create window
    HWND hWnd1 = CreateWindow(
        windowClass,
        L"1",
        WS_BORDER | WS_OVERLAPPED,
        0,
        0,
        winSize,
        winSize,
        nullptr,
        nullptr,
        GetModuleHandle(0),
        nullptr
    );
    ShowWindow(hWnd1, SW_SHOW);
    hwndList.push_back(hWnd1);

    // Create window

    /*
    HWND hWnd2 = CreateWindow(
        windowClass,
        L"2",
        WS_OVERLAPPEDWINDOW,
        2 * winSize,
        0,
        winSize,
        winSize,
        nullptr,
        nullptr,
        GetModuleHandle(0),
        nullptr
    );
    ShowWindow(hWnd2, SW_SHOW);
    hwndList.push_back(hWnd2);
    */

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_KEYDOWN) {
            switch (msg.wParam) {
            case 'W':
                circle.y -= 4;
                break;
            case 'A':
                circle.x -= 4;
                break;
            case 'S':
                circle.y += 4;
                break;
            case 'D':
                circle.x += 4;
                break;
            }
            RepaintAllWindows();
        }
        else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            /*
            for (auto& hwnd : hwndList) {
                if (msg.hwnd == hwnd) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    break; // Exit the loop after processing the message for the specified window
                }
            }
            */
        }
    }

    return EXIT_SUCCESS;
}