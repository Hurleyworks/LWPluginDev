// This header file was auto-generated by ClassMate++
// Created: 18 Feb 2020 6:02:06 pm
// Copyright (c) 2020, HurleyWorks

#pragma once

#include "LWProperties.h"
#include "LWPlugin.h"
#include "LWData.h"

struct LWModule
{
    LWModule()
    {
    }
    ~LWModule() = default;

    bool init (GlobalFunc* const g);
    LWPlugin* plugin() { return &lwPlugin; }
    LWProperties& props() { return properties; }

    LWWrapper lw;
    LWPlugin lwPlugin;
    LWProperties properties;

}; // end class LWModule