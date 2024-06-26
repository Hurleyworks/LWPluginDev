// This source file was auto-generated by ClassMate++
#include "berserkpch.h"
#include "Slider.h"
// Created: 16 Aug 2009 4:56:19 am
// Copyright (c) 2009, HurleyWorks

// ctor
Slider::Slider (ControlType type, 
				int width,
				int min,
				int max,
				const std::string& title)
	: type_(type),
	  title_(title)
{

	desc.type = LWT_RANGE;
	desc.range.width = width;
	desc.range.min = min;
	desc.range.max = max;
}

// ctor
Slider::Slider (ControlType type, const std::string& title)
	: type_(type),
	  title_(title)
{

	// percent
	desc.type = LWT_RANGE;
	desc.range.min = 0;
	desc.range.max = 100;
}

// dtor
Slider::~Slider ()
{
}

// getTitle
std::string Slider::getTitle () const
{

	return title_;
}

// getType
ControlType Slider::getType () const
{

	return type_;
}




