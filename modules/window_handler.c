#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../include/window_handler.h"
#include "../include/exit_diag.h"


LRESULT CALLBACK Window(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CLOSE: {
            exitDiag(hwnd, NULL, NULL);
        }
        case WM_DESTROY:
            PostQuitMessage(0);
        case WM_PAINT: {    // https://learn.microsoft.com/en-us/windows/win32/learnwin32/painting-the-window
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+2));
            EndPaint(hwnd, &ps);
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
