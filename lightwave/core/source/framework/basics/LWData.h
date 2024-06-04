#pragma once

#include "LWsdk.h"

static const char* LWMessageTable[] =
    {
        "HelloLW",
        "Invalid"};

struct LWMessage
{
    enum ELWMessage
    {
        HelloLW,
        Count,
        Invalid = Count
    };

    union
    {
        ELWMessage name;
        unsigned int value;
    };

    LWMessage (ELWMessage name) :
        name (name) {}
    LWMessage (unsigned int value) :
        value (value) {}
    LWMessage() :
        value (Invalid) {}
    operator ELWMessage() const { return name; }
    const char* ToString() const { return LWMessageTable[value]; }
};
