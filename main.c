#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dwmapi.h>
#include "include/window_handler.h"



int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCndLine, int nShowCmd) { // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
    const char* WINDOW_NAME = "StructDB";
    int SCREENX = GetSystemMetrics(SM_CXSCREEN);
    int SCREENY = GetSystemMetrics(SM_CYSCREEN);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = Window;
    wc.hInstance = hInst;
    wc.lpszClassName = WINDOW_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,
        WINDOW_NAME,
        "StructDB",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        SCREENX/2,
        SCREENY/2,
        NULL,
        NULL,
        hInst,
        NULL
        );
    if (hwnd == NULL) {
        return(0);
    }

    COLORREF titlebar = RGB(50, 50, 50);
    DwmSetWindowAttribute(
        hwnd,
        35,
        &titlebar,
        sizeof(titlebar)
        );

    ShowWindow(hwnd, nShowCmd);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}