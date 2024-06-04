#include "Standard.h"

int ActivateGeneric (long version, GlobalFunc* global, LWLayoutGeneric* local, void* serverData);

ServerTagInfo serverTags[] = {
    {"Simple Generic Plugin", SRVTAG_USERNAME | LANGID_USENGLISH},
    // text for button in LW gui
    {"SimpleGenericPlugin", SRVTAG_BUTTONNAME | LANGID_USENGLISH},
    {nullptr}};

ServerRecord ServerDesc[] =
    {
        {LWLAYOUTGENERIC_CLASS, pluginName.c_str(), (ActivateFunc*)ActivateGeneric, serverTags},
        {nullptr}};