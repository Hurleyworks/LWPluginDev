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
class  Intersector1
{

 public:
    // A class for intersection of intervals [u0,u1] and [v0,v1].  The end
    // points must be ordered:  u0 <= u1 and v0 <= v1.  Values of MAX_REAL
    // and -MAX_REAL are allowed, and degenerate intervals are allowed:
    // u0 = u1 or v0 = v1.
    Intersector1 (T u0, T u1, T v0, T v1);
    Intersector1 (T u[2], T v[2]);
    ~Intersector1 ();

    // Object access.
    T getU (int i) const;
    T getV (int i) const;

    // Static intersection queries.
    bool test ();
    bool find ();

 
    // Information about the intersection set.  The number of intersections
    // is 0 (intervals do not overlap), 1 (intervals are just touching), or
    // 2 (intervals intersect in an inteval).
    int getNumIntersections () const;
    T getIntersection (int i) const;

 protected:
    // The intervals to intersect.
    T mU[2], mV[2];

    // Information about the intersection set.
    T mFirstTime, mLastTime;
    int mNumIntersections;
    T mIntersections[2];
};

typedef Intersector1<float> Intersector1f;
typedef Intersector1<double> Intersector1d;