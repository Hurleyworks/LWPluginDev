/*
 * LWSDK Startup File
 * Copyright 1995,1997  NewTek, Inc.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Standard.h"

void OpenConsole()
{
    // Allocate a console for this app
    AllocConsole();

    // Redirect standard input, output, and error streams to the console
    FILE* fp;
    freopen_s (&fp, "CONIN$", "r", stdin);
    freopen_s (&fp, "CONOUT$", "w", stdout);
    freopen_s (&fp, "CONOUT$", "w", stderr);

    // Optionally, you can use C++ standard streams
    std::ios::sync_with_stdio();
}

void* Startup (void)
{
    OpenConsole();
    return (void*)4;
}

void Shutdown (void* serverData)
{
}

ServerUserName UserNames[] =
    {
        {0}};

extern ServerRecord ServerDesc[];

ModuleDescriptor _mod_descrip = {
    MOD_SYSSYNC,
    MOD_SYSVER,
    MOD_MACHINE,
    Startup,
    Shutdown,
    ServerDesc};
