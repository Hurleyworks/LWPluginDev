// This source file was auto-generated by ClassMate++
#include "berserkpch.h"
#include "Border.h"
// Created: 15 Aug 2009 9:10:09 pm
// Copyright (c) 2009, HurleyWorks

// ctor
Border::Border (int w, int h, const std::string & title)
	: title_(title)
{

	desc.type = LWT_AREA;
	desc.area.width = w;
	desc.area.height = h;
}

// dtor
Border::~Border ()
{
}

// getTitle
std::string Border::getTitle () const
{

	return title_;
}

// getType
ControlType Border::getType () const
{

	return ControlType::BorderControl;
}




