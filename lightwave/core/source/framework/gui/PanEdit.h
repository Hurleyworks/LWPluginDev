// This header file was auto-generated by ClassMate++
// Created: 15 Aug 2009 5:46:04 pm
// Copyright (c) 2009, HurleyWorks

#pragma once

#include "Control.h"

class Edit : public Control
		/// and responsibilty of class Edit
{

 public:
	Edit (ControlType type, const std::string& title = "Edit this", int width = 0);
		/// Creates a Edit instance

	~Edit ();
		/// Destroys a Edit instance

	std::string getTitle () const;

	ControlType getType () const;

 private:
    ControlType type_;
	std::string title_;

}; // end class Edit
