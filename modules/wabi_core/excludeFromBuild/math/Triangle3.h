// This header file was auto-generated by ClassMate++
// Created: 6 Mar 2009 9:34:37 pm
// Copyright (c) 2009, HurleyWorks

#pragma once


// modified from
// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//

template<class T>
class Triangle3
{

 public:
	Triangle3 ();
	Triangle3 (const Eigen::Matrix<T,3,1> pnts[3]);
	Triangle3 (const Eigen::Matrix<T,3,1> & v0,
               const Eigen::Matrix<T,3,1> & v1, 
               const Eigen::Matrix<T,3,1> & v2);
	Triangle3 (const Triangle3<T>& other);
	
	~Triangle3 ();
		
	Triangle3<T>& operator=( const Triangle3<T>& other );

	T getBound( int index ) const;
	const Eigen::Matrix<T, 3, 1> & getNormal() const { return n; }
	Eigen::Matrix<T, 3, 1> & getNormal()  { return n; }
	const Eigen::Matrix<T, 3, 1> & getCentroid() const { return c; }
	const BoundingBox3<T> & getBBox() const { return bounds; }
	Eigen::Matrix < T, 3, 1 > getVertexPos(short index);
	const Eigen::Matrix < T, 3, 1 > getVertexPos(short index) const;
	T getArea() const;

	bool findIntersect(Ray3<T> & ray);
	bool testIntersect(Ray3<T> & ray);
	
 protected:
	Eigen::Matrix<T,3,1> v_[3];
	BoundingBox3<T> bounds;
	Eigen::Matrix<T,3,1> e1;
	Eigen::Matrix<T,3,1> e2;
	Eigen::Matrix<T,3,1> e3;
	Eigen::Matrix<T,3,1> n;
	Eigen::Matrix<T,3,1> c;
	
}; // end class Triangle3


typedef Triangle3<float> Triangle3f;
typedef Triangle3<double> Triangle3d;
typedef std::vector<Triangle3f> TriVecf;
typedef std::vector<Triangle3d> TriVecd;

