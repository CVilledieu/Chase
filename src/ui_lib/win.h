#ifndef __WIN_H
#define __WIN_H

#include <windows.h>

#define MAX_TITLE_LEN 32

typedef struct WinCtx {
    HWND hwnd;
    int width;
    int height;
    char title[MAX_TITLE_LEN];
    HBRUSH bgColor;
} WinCtx;

void OpenWindow();
void WindowSize(int height, int width);

void updateWinCtx(char szTitle[MAX_TITLE_LEN], int height, int width, HBRUSH color);
WinCtx* getWinCtx();


#endif