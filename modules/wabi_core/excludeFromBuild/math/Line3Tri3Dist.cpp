// This source file was auto-generated by ClassMate++
// Created: 5 Jul 2016 10:58:30 am
// Copyright (c) 2016, HurleyWorks

// ctor
template <typename T>
Line3Tri3Dist<T>::Line3Tri3Dist (const Line3D<T>& line, const Triangle3<T>& triangle)
	: mLine(&line),
	  mTriangle(&triangle)
{
}

// dtor
template <typename T>
Line3Tri3Dist<T>::~Line3Tri3Dist ()
{	
}

template<typename T>
T Line3Tri3Dist<T>::GetSquared()
{
	// Test if line intersects triangle.  If so, the squared distance is zero.
	Eigen::Matrix<T,3,1> edge0 = mTriangle->getVertexPos(1) - mTriangle->getVertexPos(0);
	Eigen::Matrix<T,3,1> edge1 = mTriangle->getVertexPos(2) - mTriangle->getVertexPos(0);
	Eigen::Matrix<T, 3, 1> normal = edge0.cross(edge1).normalized();
	T NdD = normal.dot(mLine->direction);
	if (Math<T>::FAbs(NdD) > Math<T>::ZERO_TOLERANCE)
	{
		// The line and triangle are not parallel, so the line intersects
		// the plane of the triangle.
		Eigen::Matrix<T,3,1> diff = mLine->origin - mTriangle->getVertexPos(0);
		Eigen::Matrix<T,3,1> U, V;
		eigenEx::generateComplementBasis<T>(U, V, mLine->direction);
		T UdE0 = U.dot(edge0);
		T UdE1 = U.dot(edge1);
		T UdDiff = U.dot(diff);
		T VdE0 = V.dot(edge0);
		T VdE1 = V.dot(edge1);
		T VdDiff = V.dot(diff);
		T invDet = ((T)1) / (UdE0*VdE1 - UdE1*VdE0);

		// Barycentric coordinates for the point of intersection.
		T b1 = (VdE1*UdDiff - UdE1*VdDiff)*invDet;
		T b2 = (UdE0*VdDiff - VdE0*UdDiff)*invDet;
		T b0 = (T)1 - b1 - b2;

		if (b0 >= (T)0 && b1 >= (T)0 && b2 >= (T)0)
		{
			// Line parameter for the point of intersection.
			T DdE0 = mLine->direction.dot(edge0);
			T DdE1 = mLine->direction.dot(edge1);
			T DdDiff = mLine->direction.dot(diff);
			mLineParameter = b1*DdE0 + b2*DdE1 - DdDiff;

			// Barycentric coordinates for the point of intersection.
			mTriangleBary[0] = b0;
			mTriangleBary[1] = b1;
			mTriangleBary[2] = b2;

			// The intersection point is inside or on the triangle.
			mClosestPoint0 = mLine->origin + mLineParameter*mLine->direction;
			mClosestPoint1 = mTriangle->getVertexPos(0) + b1*edge0 + b2*edge1;

			return (T)0;
		}
	}

	// Either (1) the line is not parallel to the triangle and the point of
	// intersection of the line and the plane of the triangle is outside the
	// triangle or (2) the line and triangle are parallel.  Regardless, the
	// closest point on the triangle is on an edge of the triangle.  Compare
	// the line to all three edges of the triangle.
	T sqrDist = Math<T>::MAX_REAL;
	for (int i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
	{
		Segment3<T> segment;
		segment.center = ((T)0.5)*(mTriangle->getVertexPos(i0) + mTriangle->getVertexPos(i1));
		segment.direction = mTriangle->getVertexPos(i1)- mTriangle->getVertexPos(i0);
		segment.extent = ((T)0.5)* eigenEx::normalize(segment.direction);
		segment.computeEndPoints();

		Line3Seg3Dist<T> queryLS(*mLine, segment);
		T sqrDistTmp = queryLS.GetSquared();
		if (sqrDistTmp < sqrDist)
		{
			mClosestPoint0 = queryLS.GetClosestPoint0();
			mClosestPoint1 = queryLS.GetClosestPoint1();
			sqrDist = sqrDistTmp;

			mLineParameter = queryLS.GetLineParameter();
			T ratio = queryLS.GetSegmentParameter() / segment.extent;
			mTriangleBary[i0] = ((T)0.5)*((T)1 - ratio);
			mTriangleBary[i1] = (T)1 - mTriangleBary[i0];
			mTriangleBary[3 - i0 - i1] = (T)0;
		}
	}

	return sqrDist;
}


template
class Line3Tri3Dist<float>;

template
class Line3Tri3Dist<double>;
