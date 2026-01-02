#include "win.h"

static WinCtx g_win = {
    .hwnd = NULL,
    .width = 1080,
    .height = 1920,
    .title = "My app",
    .bgColor = NULL
};

void DrawWindow(HWND hwnd){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    // Background
    FillRect(hdc, &ps.rcPaint, g_win.bgColor);
    //DrawUI(hdc);
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            DrawWindow(hwnd);
            return 0;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: 
            return 0;
        
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void OpenWindow(){
    const char szWC_NAME[] = "MyUI_WC";

    if (g_win.bgColor == NULL) {
        g_win.bgColor = (HBRUSH)(COLOR_WINDOW + 1);
    }

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = szWC_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    g_win.hwnd = CreateWindowEx(
        0, szWC_NAME, g_win.title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        g_win.width, g_win.height,
        NULL, NULL,
        GetModuleHandle(NULL), NULL
    );

    ShowWindow(g_win.hwnd, SW_SHOW);
}


void WindowSize(int height, int width){
    g_win.height = height;
    g_win.width = width;
    if(g_win.hwnd != NULL){
        
    }
}

WinCtx* getWinCtx(){
    return &g_win;
}

void updateWinCtx(char szTitle[MAX_TITLE_LEN], int height, int width, HBRUSH color){
    g_win.height = height;
    g_win.width = width;
    strncpy(g_win.title, szTitle, MAX_TITLE_LEN-1);
    g_win.title[MAX_TITLE_LEN-1] = '\0';
    g_win.bgColor = color;
}