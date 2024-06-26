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
struct  Plane3
		///	The Plane3 class represents a half space, so the
		///	normal may point either towards or away from origin.  The
		///	plane P can be represented by Plane3 as either p or -p
		///	corresponding to the two half-spaces on either side of the
		///	plane. Any function which computes a distance will return
		///	either negative or positive values for the distance indicating
		///	which half-space the point is in. Note that reflection, and
		///	intersection functions will operate as expected.
{

	typedef std::shared_ptr<Plane3<T> > Ptr;

	Plane3();
	Plane3 (const Eigen::Matrix<T,3,1> & normal, T distance);
	Plane3 (const Eigen::Matrix<T,3,1> & point, const Eigen::Matrix<T,3,1> & normal);
	Plane3 (const Eigen::Matrix<T,3,1> & point1,
            const Eigen::Matrix<T,3,1> & point2, 
            const Eigen::Matrix<T,3,1> & point3);

	~Plane3 ();
		
	T distanceTo (const Eigen::Matrix<T,3,1> & point) const;
	bool intersect (const Line3 <T> & line, Eigen::Matrix<T,3,1> & intersection) const;
	bool intersectT (const Line3 <T> & line, T & parameter) const;
	Eigen::Matrix<T,3,1> reflectPoint (const Eigen::Matrix<T,3,1> & point) const;
	Eigen::Matrix<T,3,1> reflectVector (const Eigen::Matrix<T,3,1> & vector) const;
	void set (const Eigen::Matrix<T,3,1> & normal, T distance);
	void set (const Eigen::Matrix<T,3,1> & point, const Eigen::Matrix<T,3,1> & normal);
	void set (const Eigen::Matrix<T,3,1> & point1,
              const Eigen::Matrix<T,3,1> & point2, 
              const Eigen::Matrix<T,3,1> & point3);
	
	Eigen::Matrix<T,3,1> normal;
    T distance;

}; // end class Plane3

typedef Plane3<float> Plane3f;
typedef Plane3<double> Plane3d;
