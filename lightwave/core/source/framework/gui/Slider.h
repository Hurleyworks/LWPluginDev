// This header file was auto-generated by ClassMate++
// Created: 16 Aug 2009 4:56:19 am
// Copyright (c) 2009, HurleyWorks

#pragma once

#include "Control.h"

class Slider : public Control
		/// and responsibilty of class Slider
{

 public:
	Slider (ControlType type, 
			int width = 100,
			int min = 0,
			int max = 100,
			const std::string& title = "Slider");
		/// Creates a Slider instance

	Slider (ControlType type, const std::string& title = "Slider");
		/// Creates a Slider instance

	~Slider ();
		/// Destroys a Slider instance

	std::string getTitle () const;

	ControlType getType () const;

 private:
    ControlType type_;
	std::string title_;

}; // end class Slider
