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
class Seg3Tri3Intersect : public Intersector<T, Eigen::Matrix<T,3,1>  >
{

 public:
	Seg3Tri3Intersect (const Segment3<T>& segment, const Triangle3<T>& triangle);
	~Seg3Tri3Intersect ();

    // Object access.
	const Segment3<T>& getSegment () const { return *mSegment; }
	const Triangle3<T>& getTriangle () const { return *mTriangle; }

    // Static intersection query.
    virtual bool test ();
    virtual bool find ();

    // The intersection set.  If the segment and triangle do not intersect,
    // getQuantity() returns 0, in which case the intersection type is
    // IT_EMPTY.  If the segment and triangle intersect in a single point,
    // getQuantity() returns 1, in which case the intersection type is
    // IT_POINT and getPoint() returns the intersection point.  If the segment
    // and triangle intersect in a segment, getQuantity() returns 2, in which
    // case the intersection type is IT_SEGMENT and getPoint() returns the
    // segment endpoints.
	int getQuantity () const { return mQuantity; }
    const Eigen::Matrix<T,3,1>& getPoint (int i) const;

 private:
    using Intersector<T, Eigen::Matrix<T,3,1> >::IT_EMPTY;
    using Intersector<T, Eigen::Matrix<T,3,1> >::IT_POINT;
    using Intersector<T, Eigen::Matrix<T,3,1> >::IT_SEGMENT;
    using Intersector<T, Eigen::Matrix<T,3,1> >::intersectionType_;
	
 private:
    // The objects to intersect.
    const Segment3<T>* mSegment;
    const Triangle3<T>* mTriangle;

    // Information about the intersection set.
    int mQuantity;
    Eigen::Matrix<T,3,1> mPoint[3];
};

typedef Seg3Tri3Intersect<float> Seg3Tri3Intersectf;
typedef Seg3Tri3Intersect<double> Seg3Tri3Intersectd;