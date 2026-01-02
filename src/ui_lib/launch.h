#ifndef __LAUNCH_H
#define __LAUNCH_H

#include <windows.h>

typedef struct HookManager {
    HHOOK hook;
    char launchKey;
} HookManager;

HookManager* newHookManager();

#endif