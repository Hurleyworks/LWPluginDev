// This source file was auto-generated by ClassMate++
// Created: 19 Jul 2010 2:59:18 pm
// Copyright (c) 2010, HurleyWorks

// modified version of 
// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

// ctor
template <typename T>
Tri3Tri3Intersect<T>::Tri3Tri3Intersect (const Triangle3 <T> & triangle0,
									     const Triangle3 <T> & triangle1)
	: mTriangle0(&triangle0),
      mTriangle1(&triangle1),
	  reportCoplanarIntersections(true),
	  mQuantity(0)
{	
}

// dtor
template <typename T>
Tri3Tri3Intersect<T>::~Tri3Tri3Intersect ()
{	
}

// intersectsSegment
template <typename T>
bool Tri3Tri3Intersect<T>::intersectsSegment (const Plane <T> & plane,
											  const Triangle3 <T> & triangle, 
                                              const Eigen::Matrix <T,3,1> & end0, 
											  const Eigen::Matrix <T,3,1> & end1)
{	
	// Compute the 2D representations of the triangle vertices and the
    // segment endpoints relative to the plane of the triangle.  Then
    // compute the intersection in the 2D space.

    // Project the triangle and segment onto the coordinate plane most
    // aligned with the plane normal.
    int maxNormal = 0;
    T fmax = Math<T>::FAbs(plane.normal[0]);
    T absMax = Math<T>::FAbs(plane.normal[1]);
    if (absMax > fmax)
    {
        maxNormal = 1;
        fmax = absMax;
    }
    absMax = Math<T>::FAbs(plane.normal[2]);
    if (absMax > fmax)
    {
        maxNormal = 2;
    }

	Triangle2<T> projTri;
    Eigen::Matrix<T,2,1> projEnd0, projEnd1;
    int i;

    if (maxNormal == 0)
    {
        // Project onto yz-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri.v_[i][0] = triangle.getVertexPos(i)[1];
            projTri.v_[i][1] = triangle.getVertexPos(i)[2];
            projEnd0[0] = end0[1];
            projEnd0[1] = end0[2];
            projEnd1[0] = end1[1];
            projEnd1[1] = end1[2];
        }
    }
    else if (maxNormal == 1)
    {
        // Project onto xz-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri.v_[i][0] = triangle.getVertexPos(i)[0];
            projTri.v_[i][1] = triangle.getVertexPos(i)[2];
            projEnd0[0] = end0[0];
            projEnd0[1] = end0[2];
            projEnd1[0] = end1[0];
            projEnd1[1] = end1[2];
        }
    }
    else
    {
        // Project onto xy-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri.v_[i][0] = triangle.getVertexPos(i)[0];
            projTri.v_[i][1] = triangle.getVertexPos(i)[1];
            projEnd0[0] = end0[0];
            projEnd0[1] = end0[1];
            projEnd1[0] = end1[0];
            projEnd1[1] = end1[1];
        }
    }

	Segment2<T> projSeg(projEnd0, projEnd1);
    Seg2Tri2Intersect<T> calc(projSeg, projTri);
    if (!calc.find())
    {
        return false;
    }

    Eigen::Matrix<T,2,1> intr[2];
    if (calc.getIntersectionType() == IT_SEGMENT)
    {
        intersectionType_ = IT_SEGMENT;
        mQuantity = 2;
        intr[0] = calc.getPoint(0);
        intr[1] = calc.getPoint(1);
    }
    else
    {
		// Intersection must be a point
        debug_assert(calc.getIntersectionType() == IT_POINT);
        intersectionType_ = IT_POINT;
        mQuantity = 1;
        intr[0] = calc.getPoint(0);
    }

    // Unproject the segment of intersection.
    if (maxNormal == 0)
    {
        T invNX = ((T)1)/plane.normal[0];
        for (i = 0; i < mQuantity; ++i)
        {
            mPoint[i][1] = intr[i][0];
            mPoint[i][2] = intr[i][1];
            mPoint[i][0] = invNX*(plane.constant -
                plane.normal[1]*mPoint[i][1] -
                plane.normal[2]*mPoint[i][2]);
        }
    }
    else if (maxNormal == 1)
    {
        T invNY = ((T)1)/plane.normal[1];
        for (i = 0; i < mQuantity; ++i)
        {
            mPoint[i][0] = intr[i][0];
            mPoint[i][2] = intr[i][1];
            mPoint[i][1] = invNY*(plane.constant -
                plane.normal[0]*mPoint[i][0] -
                plane.normal[2]*mPoint[i][2]);
        }
    }
    else
    {
        T invNZ = ((T)1)/plane.normal[2];
        for (i = 0; i < mQuantity; ++i)
        {
            mPoint[i][0] = intr[i][0];
            mPoint[i][1] = intr[i][1];
            mPoint[i][2] = invNZ*(plane.constant -
						   plane.normal[0]*mPoint[i][0] -
						   plane.normal[1]*mPoint[i][1]);
        }
    }

    return true;
}

// containsPoint
template <typename T>
bool Tri3Tri3Intersect<T>::containsPoint (const Triangle3 <T> & triangle,
										  const Plane <T> & plane, 
										  const Eigen::Matrix <T,3,1> & point)
{	
	// Generate a coordinate system for the plane.  The incoming triangle has
    // vertices <V0,V1,V2>.  The incoming plane has unit-length normal N.
    // The incoming point is P.  V0 is chosen as the origin for the plane. The
    // coordinate axis directions are two unit-length vectors, U0 and U1,
    // constructed so that {U0,U1,N} is an orthonormal set.  Any point Q
    // in the plane may be written as Q = V0 + x0*U0 + x1*U1.  The coordinates
    // are computed as x0 = Dot(U0,Q-V0) and x1 = Dot(U1,Q-V0).
    Eigen::Matrix <T,3,1> U0, U1;
    generateComplementBasis(U0, U1, plane.normal);

	// Compute the planar coordinates for the points P, V1, and V2.  To
    // simplify matters, the origin is subtracted from the points, in which
    // case the planar coordinates are for P-V0, V1-V0, and V2-V0.
    Eigen::Matrix <T,3,1> PmV0 = point - triangle.getVertexPos(0);
    Eigen::Matrix <T,3,1> V1mV0 = triangle.getVertexPos(1) - triangle.getVertexPos(0);
    Eigen::Matrix <T,3,1> V2mV0 = triangle.getVertexPos(2) - triangle.getVertexPos(0);

	 // The planar representation of P-V0.
    Eigen::Matrix<T,2,1> ProjP(U0.dot(PmV0), U1.dot(PmV0));

    // The planar representation of the triangle <V0-V0,V1-V0,V2-V0>.
    Eigen::Matrix<T,2,1> ProjV[3] =
    {
        Eigen::Matrix<T,2,1>::Zero(),
        Eigen::Matrix<T,2,1>(U0.dot(V1mV0),U1.dot(V1mV0)),
        Eigen::Matrix<T,2,1>(U0.dot(V2mV0),U1.dot(V2mV0))
    };

	// Test whether P-V0 is in the triangle <0,V1-V0,V2-V0>.
    if (Query2<T>(3,ProjV).toTriangle(ProjP,0,1,2) <= 0)
    {
        // Report the point of intersection to the caller.
        intersectionType_ = IT_POINT;
        mQuantity = 1;
        mPoint[0] = point;
        return true;
    }

    return false;
}

template <typename T>
int Tri3Tri3Intersect<T>::getQuantity () const
{
    return mQuantity;
}

template <typename T>
const Eigen::Matrix<T,3,1>& Tri3Tri3Intersect<T>::getPoint (int i) const
{
	debug_assert(i >= 0 && i < 6);

    return mPoint[i];
}

// find
template <typename T>
bool Tri3Tri3Intersect<T>::find (T dist3[], T signs3[] )
{	
	int i, iM, iP;

    // Get the plane of triangle0.
    Plane<T> plane0(mTriangle0->getVertexPos(0), mTriangle0->getVertexPos(1), mTriangle0->getVertexPos(2));

	// Compute the signed distances of triangle1 vertices to plane0.  Use
    // an epsilon-thick plane test.
    int pos1, neg1, zero1, sign1[3];
    T dist1[3];
    trianglePlaneRelations(*mTriangle1, plane0, dist1, sign1, pos1, neg1, zero1);

	for( int i = 0; i < 3; i++ )
	{
		dist3[i] = dist1[i];
		signs3[i] = (float)sign1[i];
	}

	if (pos1 == 3 || neg1 == 3)
    {
        // Triangle1 is fully on one side of plane0.
        return false;
    }

	if (zero1 == 3)
    {
        // Triangle1 is contained by plane0.
        if (reportCoplanarIntersections)
        {
            return getCoplanarIntersection(plane0, *mTriangle0, *mTriangle1);
        }
        return false;
    }

	 // Check for grazing contact between triangle1 and plane0.
    if (pos1 == 0 || neg1 == 0)
    {
        if (zero1 == 2)
        {
            // An edge of triangle1 is in plane0.
            for (i = 0; i < 3; ++i)
            {
                if (sign1[i] != 0)
                {
                    iM = (i + 2) % 3;
                    iP = (i + 1) % 3;
                    return intersectsSegment(plane0, *mTriangle0, mTriangle1->getVertexPos(iM), mTriangle1->getVertexPos(iP));
                }
            }
        }
        else // zero1 == 1
        {
            // A vertex of triangle1 is in plane0.
            for (i = 0; i < 3; ++i)
            {
                if (sign1[i] == 0)
                {
                    return containsPoint(*mTriangle0, plane0, mTriangle1->getVertexPos(i));
                }
            }
        }
    }

    // At this point, triangle1 tranversely intersects plane 0.  Compute the
    // line segment of intersection.  Then test for intersection between this
    // segment and triangle 0.
    T t;
    Eigen::Matrix<T,3,1> intr0, intr1;
    if (zero1 == 0)
    {
        int iSign = (pos1 == 1 ? +1 : -1);
        for (i = 0; i < 3; ++i)
        {
            if (sign1[i] == iSign)
            {
                iM = (i + 2) % 3;
                iP = (i + 1) % 3;
                t = dist1[i]/(dist1[i] - dist1[iM]);
                intr0 = mTriangle1->getVertexPos(i) + t*(mTriangle1->getVertexPos(iM) -
                    mTriangle1->getVertexPos(i));
                t = dist1[i]/(dist1[i] - dist1[iP]);
                intr1 = mTriangle1->getVertexPos(i) + t*(mTriangle1->getVertexPos(iP) - mTriangle1->getVertexPos(i));
                return intersectsSegment(plane0, *mTriangle0, intr0, intr1);
            }
        }
    }

    // zero1 == 1
    for (i = 0; i < 3; ++i)
    {
        if (sign1[i] == 0)
        {
            iM = (i + 2) % 3;
            iP = (i + 1) % 3;
            t = dist1[iM]/(dist1[iM] - dist1[iP]);
            intr0 = mTriangle1->getVertexPos(iM) + t*(mTriangle1->getVertexPos(iP) -mTriangle1->getVertexPos(iM));
            return intersectsSegment(plane0, *mTriangle0, mTriangle1->getVertexPos(i),intr0);
        }
    }

	// Should not get here
    debug_assert(false);
    return false;
}


// find
template <typename T>
bool Tri3Tri3Intersect<T>::find ()
{	
	int i, iM, iP;

    // Get the plane of triangle0.
    Plane<T> plane0(mTriangle0->getVertexPos(0), mTriangle0->getVertexPos(1), mTriangle0->getVertexPos(2));

	// Compute the signed distances of triangle1 vertices to plane0.  Use
    // an epsilon-thick plane test.
    int pos1, neg1, zero1, sign1[3];
    T dist1[3];
    trianglePlaneRelations(*mTriangle1, plane0, dist1, sign1, pos1, neg1, zero1);

	if (pos1 == 3 || neg1 == 3)
    {
        // Triangle1 is fully on one side of plane0.
        return false;
    }

	if (zero1 == 3)
    {
        // Triangle1 is contained by plane0.
        if (reportCoplanarIntersections)
        {
            return getCoplanarIntersection(plane0, *mTriangle0, *mTriangle1);
        }
        return false;
    }

	 // Check for grazing contact between triangle1 and plane0.
    if (pos1 == 0 || neg1 == 0)
    {
        if (zero1 == 2)
        {
            // An edge of triangle1 is in plane0.
            for (i = 0; i < 3; ++i)
            {
                if (sign1[i] != 0)
                {
                    iM = (i + 2) % 3;
                    iP = (i + 1) % 3;
                    return intersectsSegment(plane0, *mTriangle0, mTriangle1->getVertexPos(iM), mTriangle1->getVertexPos(iP));
                }
            }
        }
        else // zero1 == 1
        {
            // A vertex of triangle1 is in plane0.
            for (i = 0; i < 3; ++i)
            {
                if (sign1[i] == 0)
                {
                    return containsPoint(*mTriangle0, plane0, mTriangle1->getVertexPos(i));
                }
            }
        }
    }

    // At this point, triangle1 tranversely intersects plane 0.  Compute the
    // line segment of intersection.  Then test for intersection between this
    // segment and triangle 0.
    T t;
    Eigen::Matrix<T,3,1> intr0, intr1;
    if (zero1 == 0)
    {
        int iSign = (pos1 == 1 ? +1 : -1);
        for (i = 0; i < 3; ++i)
        {
            if (sign1[i] == iSign)
            {
                iM = (i + 2) % 3;
                iP = (i + 1) % 3;
                t = dist1[i]/(dist1[i] - dist1[iM]);
                intr0 = mTriangle1->getVertexPos(i) + t*(mTriangle1->getVertexPos(iM) -
                    mTriangle1->getVertexPos(i));
                t = dist1[i]/(dist1[i] - dist1[iP]);
                intr1 = mTriangle1->getVertexPos(i) + t*(mTriangle1->getVertexPos(iP) - mTriangle1->getVertexPos(i));
                return intersectsSegment(plane0, *mTriangle0, intr0, intr1);
            }
        }
    }

    // zero1 == 1
    for (i = 0; i < 3; ++i)
    {
        if (sign1[i] == 0)
        {
            iM = (i + 2) % 3;
            iP = (i + 1) % 3;
            t = dist1[iM]/(dist1[iM] - dist1[iP]);
            intr0 = mTriangle1->getVertexPos(iM) + t*(mTriangle1->getVertexPos(iP) -mTriangle1->getVertexPos(iM));
            return intersectsSegment(plane0, *mTriangle0, mTriangle1->getVertexPos(i),intr0);
        }
    }

	// Should not get here
    debug_assert(false);
    return false;
}

// getCoplanarIntersection
template <typename T>
bool Tri3Tri3Intersect<T>::getCoplanarIntersection (const Plane <T> & plane,
													const Triangle3 <T> & tri0, 
													const Triangle3 <T> & tri1)
{	
	 // Project triangles onto coordinate plane most aligned with plane
    // normal.
    int maxNormal = 0;
    T fmax = Math<T>::FAbs(plane.normal[0]);
    T absMax = Math<T>::FAbs(plane.normal[1]);
    if (absMax > fmax)
    {
        maxNormal = 1;
        fmax = absMax;
    }
    absMax = Math<T>::FAbs(plane.normal[2]);
    if (absMax > fmax)
    {
        maxNormal = 2;
    }

    Triangle2<T> projTri0, projTri1;
	int i;
	if (maxNormal == 0)
    {
        // Project onto yz-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri0.v_[i][0] = tri0.getVertexPos(i)[1];
            projTri0.v_[i][1] = tri0.getVertexPos(i)[2];
            projTri1.v_[i][0] = tri1.getVertexPos(i)[1];
            projTri1.v_[i][1] = tri1.getVertexPos(i)[2];
        }
    }
    else if (maxNormal == 1)
    {
        // Project onto xz-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri0.v_[i][0] = tri0.getVertexPos(i)[0];
            projTri0.v_[i][1] = tri0.getVertexPos(i)[2];
            projTri1.v_[i][0] = tri1.getVertexPos(i)[0];
            projTri1.v_[i][1] = tri1.getVertexPos(i)[2];
        }
    }
    else
    {
        // Project onto xy-plane.
        for (i = 0; i < 3; ++i)
        {
            projTri0.v_[i][0] = tri0.getVertexPos(i)[0];
            projTri0.v_[i][1] = tri0.getVertexPos(i)[1];
            projTri1.v_[i][0] = tri1.getVertexPos(i)[0];
            projTri1.v_[i][1] = tri1.getVertexPos(i)[1];
        }
    }

    // 2D triangle intersection routines require counterclockwise ordering.
	Eigen::Matrix<T,2,1> save;
	Eigen::Matrix<T,2,1> edge0 = projTri0.v_[1] - projTri0.v_[0];
	Eigen::Matrix<T,2,1> edge1 = projTri0.v_[2] - projTri0.v_[0];
    if (dotPerp(edge0, edge1) < (T)0)
    {
        // Triangle is clockwise, reorder it.
		save = projTri0.v_[1];
        projTri0.v_[1] = projTri0.v_[2];
        projTri0.v_[2] = save;
    }

    edge0 = projTri1.v_[1] - projTri1.v_[0];
    edge1 = projTri1.v_[2] - projTri1.v_[0];
    if (dotPerp(edge0, edge1) < (T)0)
    {
        // Triangle is clockwise, reorder it.
        save = projTri1.v_[1];
        projTri1.v_[1] = projTri1.v_[2];
        projTri1.v_[2] = save;
    }

    Tri2Tri2Intersect<T> intr(projTri0, projTri1);
    if (!intr.find())
    {
        return false;
    }

    // Map 2D intersections back to the 3D triangle space.
    mQuantity = intr.getQuantity();
    if (maxNormal == 0)
    {
        T invNX = ((T)1)/plane.normal[0];
        for (i = 0; i < mQuantity; i++)
        {
            mPoint[i][1] = intr.getPoint(i)[0];
            mPoint[i][2] = intr.getPoint(i)[1];
            mPoint[i][0] = invNX*(plane.constant - plane.normal[1]*mPoint[i][1] - plane.normal[2]*mPoint[i][2]);
        }
    }
    else if (maxNormal == 1)
    {
        T invNY = ((T)1)/plane.normal[1];
        for (i = 0; i < mQuantity; i++)
        {
            mPoint[i][0] = intr.getPoint(i)[0];
            mPoint[i][2] = intr.getPoint(i)[1];
            mPoint[i][1] = invNY*(plane.constant -
								  plane.normal[0]*mPoint[i][0] -
								  plane.normal[2]*mPoint[i][2]);
        }
    }
    else
    {
        T invNZ = ((T)1)/plane.normal[2];
        for (i = 0; i < mQuantity; i++)
        {
            mPoint[i][0] = intr.getPoint(i)[0];
            mPoint[i][1] = intr.getPoint(i)[1];
            mPoint[i][2] = invNZ*(plane.constant -
						   plane.normal[0]*mPoint[i][0] -
						   plane.normal[1]*mPoint[i][1]);
        }
    }

    intersectionType_ = IT_PLANE;
    
	return true;
}

// test
template <typename T>
bool Tri3Tri3Intersect<T>::test ()
{	
	// Get edge vectors for triangle0.
    Matrix<T,3,1> E0[3] =
    {
		mTriangle0->getVertexPos(1) -  mTriangle0->getVertexPos(0),
		mTriangle0->getVertexPos(2) -  mTriangle0->getVertexPos(1),
		mTriangle0->getVertexPos(0) -  mTriangle0->getVertexPos(2)
    };

	 // Get normal vector of triangle0.
    Matrix<T,3,1> N0 = mTriangle0->getNormal(); 
	N0.normalize();

	 // Project triangle1 onto normal line of triangle0, test for separation.
    T N0dT0V0 = N0.dot(mTriangle0->getVertexPos(0));
	T min1, max1;
    projectOntoAxis(*mTriangle1, N0, min1, max1);
    if (N0dT0V0 < min1 || N0dT0V0 > max1)
    {
        return false;
    }

	// Get edge vectors for triangle1.
    Matrix<T,3,1> E1[3] =
    {
		mTriangle1->getVertexPos(1) -  mTriangle1->getVertexPos(0),
		mTriangle1->getVertexPos(2) -  mTriangle1->getVertexPos(1),
		mTriangle1->getVertexPos(0) -  mTriangle1->getVertexPos(2)
    };

    // Get normal vector of triangle1.
    Matrix<T,3,1> N1 = mTriangle1->getNormal(); 
	N1.normalize();

	Matrix<T,3,1> dir;
    T min0, max0;
    int i0, i1;

	Matrix<T,3,1> N0xN1 = N0.cross(N1);
	N0xN1.normalize();
    if (N0xN1.dot(N0xN1) >= Math<T>::ZERO_TOLERANCE)
    {
		// Triangles are not parallel.
		
        // Project triangle0 onto normal line of triangle1, test for
        // separation.
        T N1dT1V0 = N1.dot(mTriangle1->getVertexPos(0));
        projectOntoAxis(*mTriangle0, N1, min0, max0);
        if (N1dT1V0 < min0 || N1dT1V0 > max0)
        {
            return false;
        }

        // Directions E0[i0]xE1[i1].
        for (i1 = 0; i1 < 3; ++i1)
        {
            for (i0 = 0; i0 < 3; ++i0)
            {
                dir = E0[i0].cross(E1[i1]);
				dir.normalize();
                projectOntoAxis(*mTriangle0, dir, min0, max0);
                projectOntoAxis(*mTriangle1, dir, min1, max1);
                if (max0 < min1 || max1 < min0)
                {
                    return false;
                }
            }
        }

        // The test query does not know the intersection set.
        intersectionType_ = IT_OTHER;
	}
	else  // Triangles are parallel (and, in fact, coplanar).
    {
        // Directions N0xE0[i0].
        for (i0 = 0; i0 < 3; ++i0)
        {
            dir = N0.cross(E0[i0]);
			dir.normalize();
            projectOntoAxis(*mTriangle0, dir, min0, max0);
            projectOntoAxis(*mTriangle1, dir, min1, max1);
            if (max0 < min1 || max1 < min0)
            {
                return false;
            }
        }

        // Directions N1xE1[i1].
        for (i1 = 0; i1 < 3; ++i1)
        {
            dir = N1.cross(E1[i1]);
			dir.normalize();
            projectOntoAxis(*mTriangle0, dir, min0, max0);
            projectOntoAxis(*mTriangle1, dir, min1, max1);
            if (max0 < min1 || max1 < min0)
            {
                return false;
            }
        }

        intersectionType_ = IT_PLANE;
    }
	 
	return true;
}

// projectOntoAxis
template <typename T>
void Tri3Tri3Intersect<T>::projectOntoAxis (const Triangle3 <T> & triangle,
											   const Matrix <T, 3, 1> & axis, 
											   T & fmin, 
											   T & fmax)
{
	T dot0 = axis.dot(triangle.getVertexPos(0));
    T dot1 = axis.dot(triangle.getVertexPos(1));
    T dot2 = axis.dot(triangle.getVertexPos(2));

	fmin = dot0;
    fmax = fmin;

    if (dot1 < fmin)
    {
        fmin = dot1;
    }
    else if (dot1 > fmax)
    {
        fmax = dot1;
    }

    if (dot2 < fmin)
    {
        fmin = dot2;
    }
    else if (dot2 > fmax)
    {
        fmax = dot2;
    }
}

// trianglePlaneRelations
template <typename T>
void Tri3Tri3Intersect<T>::trianglePlaneRelations (const Triangle3 <T> & triangle,
												   const Plane <T> & plane, 
												   T distance[3], 
												   int sign[3], 
												   int & positive, 
												   int & negative, 
												   int & zero)
{	
	// Compute the signed distances of triangle vertices to the plane.  Use
    // an epsilon-thick plane test.
    positive = 0;
    negative = 0;
    zero = 0;
    for (int i = 0; i < 3; ++i)
    {
        distance[i] = plane.distanceTo(triangle.getVertexPos(i));
        if (distance[i] > Math<T>::ZERO_TOLERANCE)
        {
            sign[i] = 1;
            positive++;
        }
        else if (distance[i] < -Math<T>::ZERO_TOLERANCE)
        {
            sign[i] = -1;
            negative++;
        }
        else
        {
            distance[i] = (T)0;
            sign[i] = 0;
            zero++;
        }
    }
}

// Explicit instantiation.
template 
class Tri3Tri3Intersect<float>;

template 
class Tri3Tri3Intersect<double>;




