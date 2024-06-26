// This header file was auto-generated by ClassMate++
// Created: 29 Jul 2009 11:33:13 pm
// Copyright (c) 2009, HurleyWorks

#pragma once

template <typename T>
class Box3
{

 public:
	Box3 ();
	Box3 (Eigen::Matrix<T,3,1> middle);
	Box3 (const Eigen::Matrix<T,3,1> & middle,
          const Eigen::Matrix<T,3,1> * axis, 
          const T * extent);
	Box3 (const Eigen::Matrix<T,3,1> & middle, 
          const T * extent);
	Box3 ( const Box3<T>& other);
	
	~Box3 ();
		
	void getPnts (Eigen::Matrix<T,3,1> pnts[8]) const;

	Eigen::Matrix<T,3,1> center;
	Eigen::Matrix<T,3,1> axis[3];
	T extent[3];

}; // end class Box3

typedef Box3<float> Box3f;
typedef Box3<double> Box3d;

// ctor
template <typename T>
Box3<T>::Box3 ()
	: center(Eigen::Matrix<T,3,1>(1.0,1.0,1.0))
{	
	// create a unit cube centered at the origin
	axis[0] = Eigen::Matrix<T,3,1>(1.0, 0.0, 0.0);
	axis[1] = Eigen::Matrix<T,3,1>(0.0, 1.0, 0.0);
	axis[2] = Eigen::Matrix<T,3,1>(0.0, 0.0, 1.0);

	for( int i = 0; i < 3; i++ )
		extent[i] = .5;
}

// ctor
template <typename T>
Box3<T>::Box3 ( Eigen::Matrix<T,3,1> middle )
	: center(middle)
{	
	// create a unit cube centered at center
	axis[0] = Eigen::Matrix<T,3,1>(1.0, 0.0, 0.0);
	axis[1] = Eigen::Matrix<T,3,1>(0.0, 1.0, 0.0);
	axis[2] = Eigen::Matrix<T,3,1>(0.0, 0.0, 1.0);

	for( int i = 0; i < 3; i++ )
		extent[i] = .5;
}

// ctor
template <typename T>
Box3<T>::Box3 (const Eigen::Matrix<T,3,1> & middle,
               const Eigen::Matrix<T,3,1> * axis, 
               const T * extent)
	: center(middle)
{	
	for (int i = 0; i < 3; i++)
    {
        this->axis[i] = axis[i];
        this->extent[i] = extent[i];
    }
}

// ctor
template <typename T>
Box3<T>::Box3 (const Eigen::Matrix<T,3,1> & middle,
               const T * extent)
	: center(middle)
{	
	// make the box axis aligned
	axis[0] = Eigen::Matrix<T,3,1>(1.0, 0.0, 0.0);
	axis[1] = Eigen::Matrix<T,3,1>(0.0, 1.0, 0.0);
	axis[2] = Eigen::Matrix<T,3,1>(0.0, 0.0, 1.0);

	for (int i = 0; i < 3; i++)
        this->extent[i] = extent[i];
}

template <typename T>
Box3<T>::Box3 ( const Box3<T>& other )
{	
	for( int i = 0; i < 3; i++ )
	{
		axis[i] = other.axis[i];
		extent[i] = other.extent[i];
	}
	center = other.center;
}

// dtor
template <typename T>
Box3<T>::~Box3 ()
{	
}

// getPnts
template <typename T>
void Box3<T>::getPnts (Eigen::Matrix<T,3,1> pnts[8]) const
{	
	Eigen::Matrix<T,3,1> size[3] =
    {
        extent[0]*axis[0],
        extent[1]*axis[1],
        extent[2]*axis[2]
    };

    pnts[0] = center - size[0] - size[1] - size[2];
    pnts[1] = center + size[0] - size[1] - size[2];
    pnts[2] = center + size[0] + size[1] - size[2];
    pnts[3] = center - size[0] + size[1] - size[2];
    pnts[4] = center - size[0] - size[1] + size[2];
    pnts[5] = center + size[0] - size[1] + size[2];
    pnts[6] = center + size[0] + size[1] + size[2];
    pnts[7] = center - size[0] + size[1] + size[2];
}


