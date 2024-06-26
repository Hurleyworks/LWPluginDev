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

class  Query
{
    // Abstract base class
 protected:
    Query ();

 public:
    virtual ~Query ();

    // Run-time type information.
    enum Type
    {
        QT_INT64,
        QT_INTEGER,
        QT_RATIONAL,
        QT_REAL,
        QT_FILTERED
    };

    virtual Type getType () const = 0;

    // Support for ordering a set of unique indices into the vertex pool.  On
    // output it is guaranteed that:  v0 < v1 < v2.  This is used to guarantee
    // consistent queries when the vertex ordering of a primitive is permuted,
    // a necessity when using floating-point arithmetic that suffers from
    // numerical round-off errors.  The input indices are considered the
    // positive ordering.  The output indices are either positively ordered
    // (an even number of transpositions occurs during sorting) or negatively
    // ordered (an odd number of transpositions occurs during sorting).  The
    // functions return 'true' for a positive ordering and 'false' for a
    // negative ordering.
    static bool sort (int& v0, int& v1);
    static bool sort (int& v0, int& v1, int& v2);
    static bool sort (int& v0, int& v1, int& v2, int& v3);
};
