// This header file was auto-generated by ClassMate++
// Created: 15 Aug 2009 9:10:09 pm
// Copyright (c) 2009, HurleyWorks

#pragma once

#include "Control.h"

class Border : public Control
		/// and responsibilty of class Border
{

 public:
	Border (int w, int h, const std::string & title = "");
		/// Creates a Border instance

	~Border ();
		/// Destroys a Border instance

	std::string getTitle () const;

	ControlType getType () const;

 private:
	std::string title_;

}; // end class Border
