#include "my_ui.h"

#define WND_TITLE_SIZE 32

typedef struct Hooks {
    HWND hWindow;
    HHOOK hKeys;
} Hooks;

typedef struct MyUI{
    const char szTITLE[WND_TITLE_SIZE];
} MyUI;

static MyUI g_MyUI;
static Hooks g_HookState;


int WINAPI hEarlyShutdown(DWORD msg){
    switch(msg){
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            UnhookWindowsHookEx(g_HookState.hKeys);
            return 1;
    }
    return 0;
}

LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0 || (wParam != WM_KEYDOWN && wParam != WM_SYSKEYDOWN)){
        return CallNextHookEx(g_HookState.hKeys, nCode, wParam, lParam);
    }
    KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

    printf("Key pressed: Virtual Key Code = 0x%X\n", pKeyboard->vkCode);
    
    // Example: Detect Ctrl+S
    if (pKeyboard->vkCode == 'S' && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
        printf("Ctrl+S detected!\n");                        
    }
    return CallNextHookEx(g_HookState.hKeys, nCode, wParam, lParam);
}

void new_hKeys(){
    g_HookState.hKeys = SetWindowsHookEx(
        WH_KEYBOARD_LL,           // Hook type (low-level keyboard)
        keyHookProc,             // Callback function
        NULL,                     // hInstance (NULL for low-level hooks)
        0                         // Thread ID (0 = all threads)
    );

    SetConsoleCtrlHandler(hEarlyShutdown, 1);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            //DrawUI(hdc);
            EndPaint(hwnd, &ps);
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

void new_hWindow(const char szTITLE[]){
    const char szWC_NAME[] = "__My_UI_WC";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = szWC_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);


    g_HookState.hWindow = CreateWindowEx(
        0, szWC_NAME, szTITLE,
         WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        400, 300, 
        NULL, NULL, 
        GetModuleHandle(NULL), NULL
    );

    ShowWindow(g_HookState.hWindow, 1);
}



void init_MyUi(int keyComboLaunch){
    if(keyComboLaunch){
        new_hKeys();
    }
    
}

void Run(){
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}