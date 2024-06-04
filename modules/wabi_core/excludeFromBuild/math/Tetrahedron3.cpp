// This source file was auto-generated by ClassMate++
// Created: 19 Jul 2010 2:59:18 pm
// Copyright (c) 2010, HurleyWorks

;

// ctor
template<class T>
Tetrahedron3<T>::Tetrahedron3 ()
{	TRACE("Tetrahedron3<T>::Tetrahedron3")

}

// ctor
template<class T>
Tetrahedron3<T>::Tetrahedron3 (const Tetrahedron3<T>& other)
{	TRACE("Tetrahedron3<T>::Tetrahedron3")

	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];
}

// ctor
template<class T>
Tetrahedron3<T>::Tetrahedron3 (const Eigen::Matrix<T,3,1> pnts[4])
{	TRACE("Tetrahedron3<T>::Tetrahedron3")

	for( int i = 0; i < 4; i++ )
		v[i] = pnts[i];

}

// ctor
template<class T>
Tetrahedron3<T>::Tetrahedron3 (const Eigen::Matrix<T,3,1> & v0,
							   const Eigen::Matrix<T,3,1> & v1, 
							   const Eigen::Matrix<T,3,1> & v2,
							   const Eigen::Matrix<T,3,1> & v3)
{	TRACE("Tetrahedron3<T>::Tetrahedron3")

	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;

}

// ctor
template<class T>
Tetrahedron3<T>::Tetrahedron3 (const Triangle3<T> triangle, float height)
{	TRACE("Tetrahedron3<T>::Tetrahedron3")

	Matrix<T,3,1> centroid(0.0f, 0.0f, 0.0f);
	for( int i = 0; i < 3; i++ )
	{
		Matrix<T,3,1> pos = triangle.getVertexPos(i);
		centroid += pos;
		v[i] = pos;
	}

	centroid /= 3;
	Matrix<T,3,1> normal = triangle.getNormal();
	normal.normalize();
	v[3] = centroid + height * normal;
}

// dtor
template<class T>
Tetrahedron3<T>::~Tetrahedron3 ()
{	TRACE("Tetrahedron3<T>::~Tetrahedron3")
}

template<class T>
Tetrahedron3<T>& Tetrahedron3<T>::operator=( const Tetrahedron3<T>& other )
{	TRACE("Tetrahedron3::operator =")

	v[0] = other.v[0];
	v[1] = other.v[1];
	v[2] = other.v[2];
	v[3] = other.v[3];

	return *this;
}

// getFaceIndices
template<class T>
void Tetrahedron3<T>::getFaceIndices (int face, int index[3]) const
{	TRACE("Tetrahedron3::getFaceIndices")
	
	debug_assert(face >= 0 && face <= 3 );

    if (face == 0)
    {
        index[0] = 0;
        index[1] = 1;
        index[2] = 2;
    }
    else if (face == 1)
    {
        index[0] = 3;
        index[1] = 1;
        index[2] = 0;
    }
    else if (face == 2)
    {
        index[0] = 2;
        index[1] = 3;
        index[2] = 0;
    }
    else  // face == 3 (no index validation is performed)
    {
        index[0] = 3;
        index[1] = 2;
        index[2] = 1;
    }
}



template
class Tetrahedron3<float>;

template
class Tetrahedron3<double>;

