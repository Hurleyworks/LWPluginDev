#pragma once

#include <wabi_core/wabi_core.h>

// LWSDK
#include <lwserver.h>
#include <lwmodule.h>
#include <lwio.h>
#include <lwmaster.h>
#include <lwcamera.h>
#include <lwdisplce.h>
#include <lwmotion.h>
#include <lwcustobj.h>
#include <lwtool.h>
#include <lwmeshedt.h>
#include <lwnodes.h>
#include <lwgeneric.h>
#include <lwhost.h>
#include <lwpanel.h>
#include <lwxpanel.h>
#include <lwrender.h>
#include <lwvpobject.h>
#include <lwmodtool.h>
#include <lwsurf.h>
#include <lwobjrep.h>
#include <lwlaytool.h>
#include <lwinstancing.h>
#include <lwcomring.h>
#include <lwtimer.h>
#include <lwgizmo.h>
#include <lwtypes.h>
#include <lwspatialquery.h>
#include <lwfilter.h>
#include <lwvparm.h>
#include <lwobjimp.h>
#include <lwmodeler.h>
#include <lwmaster.h>
#include <lwcommand.h>

// #define LWCOMMANDFUNC_GLOBAL "LW Command Interface"
// typedef int LWCommandFunc(const char* cmd);

template <class T>
T* getCompatibleVersion (const char* version, GlobalFunc* global, int& currentVersion)
{
    if (!global) return NULL;

    std::string versionString (version);
    size_t lastSpace = versionString.find_last_of (" ");
    std::string typeName = versionString.substr (0, lastSpace);
    std::string versionNumber = versionString.substr (lastSpace + 1);
    int num = atoi (versionNumber.c_str());

    // find a version number that works
    while (!(T*)global (versionString.c_str(), GFUSE_TRANSIENT))
    {
        --num;
        if (num > 0)
            versionString = typeName + " " + std::to_string (num);
        else if (num == 0)
            versionString = typeName; // xpanel
        else if (num < 0)
            break;
    }

    currentVersion = num;

    return (T*)global (versionString.c_str(), GFUSE_TRANSIENT);
}