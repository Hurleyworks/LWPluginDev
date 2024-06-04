// This header file was auto-generated by ClassMate++
// Created: 29 Jul 2009 11:33:13 pm
// Copyright (c) 2009, HurleyWorks

// modified version of 
// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

#pragma once

template <typename T>
class Tri2Tri2Intersect : public Intersector<T, Eigen::Matrix<T,2,1>  >
		/// TODO: Add a comment about the role
		/// and responsibilty of class Tri2Tri2Intersect
{

 public:
	Tri2Tri2Intersect (const Triangle2 <T> & triangle0,
                       const Triangle2 <T> & triangle1);
		/// Creates a Tri2Tri2Intersect instance

	~Tri2Tri2Intersect ();
		/// Destroys a Tri2Tri2Intersect instance

	bool find ();
		/// TODO: Add a comment for the find method

	bool test ();
		/// TODO: Add a comment for the test method
	 
	// Information about the intersection set.
	int getQuantity () const { return mQuantity; }
	const Eigen::Matrix<T,2,1>& getPoint (int i) const ;
	
 private:
    using Intersector<T, Eigen::Matrix<T,2,1> >::IT_EMPTY;
    using Intersector<T, Eigen::Matrix<T,2,1> >::IT_POINT;
    using Intersector<T, Eigen::Matrix<T,2,1> >::IT_SEGMENT;
    using Intersector<T, Eigen::Matrix<T,2,1> >::intersectionType_;

 private:
	// The objects to intersect.
    const Triangle2<T>* mTriangle0;
    const Triangle2<T>* mTriangle1;

	 // Information about the intersection set.
    int mQuantity;
    Eigen::Matrix<T,2,1> mPoint[6];

	static void clipConvexPolygonAgainstLine (const Eigen::Matrix<T,2,1>& N,
											   T c, int& quantity, Eigen::Matrix<T,2,1> V[6]);

};