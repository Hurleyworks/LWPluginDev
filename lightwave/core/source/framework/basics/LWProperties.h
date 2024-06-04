
#pragma once

#include "LWsdk.h"

static const char* WorkSpaceTable[] =
    {
        "LW",
        "Invalid"};

struct WorkSpace
{
    enum EWorkSpace
    {
        LW,
        Count,
        Invalid = Count
    };

    union
    {
        EWorkSpace name;
        unsigned int value;
    };

    WorkSpace (EWorkSpace name) :
        name (name) {}
    WorkSpace (unsigned int value) :
        value (value) {}
    WorkSpace() :
        value (Invalid) {}
    operator EWorkSpace() const { return name; }
    const char* ToString() const { return WorkSpaceTable[value]; }
};

static const char* LWKeyTable[] =
    {
        "WorkSpace",

        "Invalid"};

struct LWKey
{
    enum ELWKey
    {
        WorkSpace,

        Count,
        Invalid = Count
    };

    union
    {
        ELWKey name;
        unsigned int value;
    };

    LWKey (ELWKey name) :
        name (name) {}
    LWKey (unsigned int value) :
        value (value) {}
    LWKey() :
        value (Invalid) {}
    operator ELWKey() const { return name; }
    const char* ToString() const { return LWKeyTable[value]; }
    static LWKey FromString (const char* str) { return mace::TableLookup (str, LWKeyTable, Count); }
};

typedef AnyValue<LWKey> LWProperties;