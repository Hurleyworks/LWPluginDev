// This source file was auto-generated by ClassMate++
#include "berserkpch.h"
#include "Opengl.h"
// Created: 15 Aug 2009 9:10:09 pm
// Copyright (c) 2009, HurleyWorks

// ctor
Opengl::Opengl (int w, int h, const std::string & title)
	: title_(title)
{

	desc.type = LWT_AREA;
	desc.area.width = w;
	desc.area.height = h;
}

// dtor
Opengl::~Opengl ()
{
}

// getTitle
std::string Opengl::getTitle () const
{

	return title_;
}

// getType
ControlType Opengl::getType () const
{

	return ControlType::OpenGLControl;
}



