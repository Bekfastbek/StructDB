#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dwmapi.h>
// #include <stdio.h>
#include "../include/exit_diag.h"
#define BUTTON_YES 6767
#define BUTTON_NO 676767
static char* g_message = NULL;
static char* g_caption = NULL;



LRESULT CALLBACK fancyExit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            CreateWindow(
                "BUTTON",
                "YES",
                WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                200,
                90,
                50,
                30,
                hwnd,
                (HMENU)BUTTON_YES,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
                );

            CreateWindow(
                "BUTTON",
                "NO",
                WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                260,
                90,
                50,
                30,
                hwnd,
                (HMENU)BUTTON_NO,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
                );
            return 0;
        }
        case WM_COMMAND: {
            if(LOWORD(wParam) == BUTTON_YES) {
                DestroyWindow(hwnd);
            } else if (LOWORD(wParam) == BUTTON_NO) {
                PostQuitMessage(0);
            }
            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+2));
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            if (g_message) {
                TextOutA(hdc, 20, 20, g_message, lstrlenA(g_message));
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



void exitDiag(HWND hParent, char* message, char* caption) {
    if(caption == NULL) {
        caption = "Warning!";
    }
    if (message==NULL) {
        message = "Are you sure you want to exit?";
    }
    int SCREENX = GetSystemMetrics(SM_CXSCREEN) / 5;
    int SCREENY = GetSystemMetrics(SM_CYSCREEN) / 8;
    RECT rcClient;
    GetWindowRect(hParent, &rcClient);
    int parentWidth  = rcClient.right - rcClient.left;
    int parentHeight = rcClient.bottom - rcClient.top;
    int parentCenterX = rcClient.left + (parentWidth / 2);
    int parentCenterY = rcClient.top + (parentHeight / 2);
    int xPos = parentCenterX - (SCREENX / 2);
    int yPos = parentCenterY - (SCREENY / 2);
    // printf("Screen X pos: %d \n Screen Y pos: %d\n Window X pos: %d\n Window Y pos: %d", SCREENX, SCREENY, xPos, yPos);
    g_message = message;
    g_caption = caption;
    const char* DIAG_NAME = "Exit Dialog";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = fancyExit;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = DIAG_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);

    if (!RegisterClass(&wc)) {
    }

    HWND hDialog = CreateWindowEx(
        WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
        DIAG_NAME, caption,
        WS_VISIBLE | WS_POPUP | WS_CAPTION | WS_SYSMENU,
        xPos,
        yPos,
        SCREENX,
        SCREENY,
        hParent,
        NULL,
        wc.hInstance,
        NULL
        );
    if (!hDialog) {
        return;
    }
    EnableWindow(hParent, FALSE);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    EnableWindow(hParent, TRUE);
    SetActiveWindow(hParent);
}