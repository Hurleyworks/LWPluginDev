// This header file was auto-generated by ClassMate++
// Created: 20 Nov 2009 1:38:04 pm
// Copyright (c) 2009, HurleyWorks

#pragma once

struct Tri
{
	Tri()
	{
		index[0] = index[1] = index[2] = -1;
	}

	long index[3];
};


struct TripleInfo
{
	TripleInfo()
		: outputTris(0),
		  count(0)
	{}
	~TripleInfo()
	{
		delete[] outputTris;
	}
	Tri*  outputTris;
	int count;
};
