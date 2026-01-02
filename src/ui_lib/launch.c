#include "launch.h"

static HookManager g_mHook;

int WINAPI hEarlyShutdown(DWORD msg){
    switch(msg){
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            UnhookWindowsHookEx(g_mHook.hook);
            return 1;
    }
    return 0;
}

LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0 || (wParam != WM_KEYDOWN && wParam != WM_SYSKEYDOWN) || g_mHook.launchKey == 0){
        return CallNextHookEx(g_mHook.hook, nCode, wParam, lParam);
    }
    KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

    printf("Key pressed: Virtual Key Code = 0x%X\n", pKeyboard->vkCode);
    
    // Example: Detect Ctrl+S
    if (pKeyboard->vkCode == g_mHook.launchKey && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
        printf("Ctrl+S detected!\n");                        
    }
    return CallNextHookEx(g_mHook.hook, nCode, wParam, lParam);
}

HookManager* newHookManager(char key){
    g_mHook.hook = SetWindowsHookEx(
        WH_KEYBOARD_LL,           // Hook type (low-level keyboard)
        keyHookProc,             // Callback function
        NULL,                     // hInstance (NULL for low-level hooks)
        0                         // Thread ID (0 = all threads)
    );
    g_mHook.launchKey = key;
    SetConsoleCtrlHandler(hEarlyShutdown, 1);
    return &g_mHook;
}