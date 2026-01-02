#ifndef __MY_UI_H
#define __MY_UI_H

#include <windows.h>
#include "win.h"
#include "launch.h"

typedef struct MyUI{
    WndCtx* wnd;
    HookCtx* hook;
} MyUI;

MyUI* createMyUi(char* title);
void Run();

#endif