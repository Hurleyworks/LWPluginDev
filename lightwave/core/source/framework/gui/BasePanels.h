// This header file was auto-generated by ClassMate++
// Created: 11 Aug 2009 6:00:18 am
// Copyright (c) 2009, HurleyWorks

#pragma once

#include "Control.h"

class BasePanels
/// and responsibilty of class BasePanels
{
 public:
    typedef std::map<LWControl*, Control::Ptr> ControlMap;

 public:
    virtual ~BasePanels();
    /// Destroys a BasePanels instance

    void addControl (Control::Ptr control, void* userData = nullptr);

    void open (int flags = Blocking | Cancel | Resize);

    void close();

    void draw (DrMode mode);

    void destroy();

    void setPosition (int x, int y);

    void setSize (int w, int h);

    void setSize (int minW, int minH, int maxW, int maxH);

    void setUserData (void* userData);

    void setControlCallback (LWCtlEventHook callback);

    void setPanDrawCallback (LWPanDrawHook callback);

    void setPanKeyCallback (LWPanKeyHook callback);

    void setPanMouseCallback (LWPanMouseHook callback);

    void setPanMouseWheelCallback (LWPanMouseHook callback);

    void setPanUserCallback (LWPanHook callback);

    void setPanelCloseCallback (LWPanHook callback);

    void setPanelResizeCallback (LWPanResizeHook callback);

    Control::Ptr find (LWControlID control);

    DrawFuncs* getDrawFunctions();

    int handle (int flags = EVNT_BLOCKING);

    LWPanelFuncs* getPanelFuncs() { return panelFuncs_; }
    LWPanelID getPanelID() { return panelID_; }

 protected:
    BasePanels (GlobalFunc* global, const std::string& title = "My LW Panel");
    /// Creates a BasePanels instance

 private:
    GlobalFunc* global_;
    std::string title_;
    LWPanelID panelID_;
    LWPanelFuncs* panelFuncs_;
    LWCtlEventHook ctrlEventCallback_;
    static ControlMap controls_;

}; // end class BasePanels

// getDrawFunctions
inline DrawFuncs* BasePanels::getDrawFunctions()
{
    return panelFuncs_->drawFuncs;
}
