#include "my_ui.h"
#include "win.h"

MyUI* createMyUi(char launchKey){
    MyUI* ui = malloc(sizeof(MyUI));
    ui->hook = newHookManager(launchKey);
    ui->wnd = newWinManager();
    
    return ui;
}


// void launchCombo(MyUI* ui, char c){
    
// }

void Run(){
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}