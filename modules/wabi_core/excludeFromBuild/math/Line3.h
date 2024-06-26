// This header file was auto-generated by ClassMate++
// Created: 6 Mar 2009 9:34:37 pm
// Copyright (c) 2009, HurleyWorks

///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2002, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////

#pragma once

template<class T>
struct Line3
{
	typedef std::shared_ptr<Line3<T> > Ptr;

	Line3 ();
	Line3(const Eigen::Matrix <T, 3, 1> & point1, const Eigen::Matrix <T, 3, 1> & point2);
	~Line3 ();
		
	void set (const Eigen::Matrix <T,3,1> & point1, const Eigen::Matrix <T,3,1> & point2);
	Eigen::Matrix <T,3,1> operator() (T parameter) const;
	Eigen::Matrix<T,3,1> closestPointTo (const Eigen::Matrix<T,3,1> & point) const;
	Eigen::Matrix<T,3,1> closestPointTo (const Line3 <T> & line) const;
	T distanceTo (const Eigen::Matrix<T,3,1> & point) const;
	T distanceTo (const Line3 <T> & line) const;
	
	Eigen::Matrix <T,3,1>  pos;
    Eigen::Matrix <T,3,1>  dir;

}; // end class Line3

typedef Line3<float> Line3f;
typedef Line3<double> Line3d;

// Wild Magic version
template <typename T>
class Line3D
{
public:
	// The line is represented as P+t*D where P is the line origin, D is a
	// unit-length direction vector, and t is any real number.  The user must
	// ensure that D is indeed unit length.

	// Construction and destruction.
	Line3D() {} // uninitialized
	~Line3D() {}

	Line3D(const Eigen::Matrix <T, 3, 1> & o, const Eigen::Matrix <T, 3, 1>& d)
		: origin(o),
		  direction(d)
	{
		
	}

	Eigen::Matrix <T, 3, 1> origin, direction;
};

typedef Line3D<float> Line3Df;
typedef Line3D<double> Line3Dd;


