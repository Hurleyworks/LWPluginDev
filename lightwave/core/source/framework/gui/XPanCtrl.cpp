// This source file was auto-generated by ClassMate++
#include "berserkpch.h"
#include "XPanCtrl.h"
// Created: 15 Aug 2009 9:10:09 pm
// Copyright (c) 2009, HurleyWorks

// ctor
XPanCtrl::XPanCtrl (LWXPanelID xpanel, const std::string & title)
	: title_(title)
{

	desc.type = LWT_XPANEL;
	desc.xpanel.xpan = xpanel;
}

// dtor
XPanCtrl::~XPanCtrl ()
{
}

// getTitle
std::string XPanCtrl::getTitle () const
{

	return title_;
}

// getType
ControlType XPanCtrl::getType () const
{

	return ControlType::XPanelControl;
}



