// This source file was auto-generated by ClassMate++
// Created: 5 Jul 2016 10:58:30 am
// Copyright (c) 2016, HurleyWorks

// ctor
template <typename T>
Line3Seg3Dist<T>::Line3Seg3Dist (const Line3D<T>& line, const Segment3<T>& segment)
	: mLine(&line),
	  mSegment(&segment)
{
}

// dtor
template <typename T>
Line3Seg3Dist<T>::~Line3Seg3Dist ()
{	
}

template<typename T>
T Line3Seg3Dist<T>::GetSquared()
{
	Eigen::Matrix<T,3,1> diff = mLine->origin - mSegment->center;
	T a01 = -mLine->direction.dot(mSegment->direction);
	T b0 = diff.dot(mLine->direction);
	T c = diff.squaredNorm();
	T det = Math<T>::FAbs((T)1 - a01*a01);
	T b1, s0, s1, sqrDist, extDet;

	if (det >= Math<T>::ZERO_TOLERANCE)
	{
		// The line and segment are not parallel.
		b1 = -diff.dot(mSegment->direction);
		s1 = a01*b0 - b1;
		extDet = mSegment->extent*det;

		if (s1 >= -extDet)
		{
			if (s1 <= extDet)
			{
				// Two interior points are closest, one on the line and one
				// on the segment.
				T invDet = ((T)1) / det;
				s0 = (a01*b1 - b0)*invDet;
				s1 *= invDet;
				sqrDist = s0*(s0 + a01*s1 + ((T)2)*b0) +
					s1*(a01*s0 + s1 + ((T)2)*b1) + c;
			}
			else
			{
				// The endpoint e1 of the segment and an interior point of
				// the line are closest.
				s1 = mSegment->extent;
				s0 = -(a01*s1 + b0);
				sqrDist = -s0*s0 + s1*(s1 + ((T)2)*b1) + c;
			}
		}
		else
		{
			// The end point e0 of the segment and an interior point of the
			// line are closest.
			s1 = -mSegment->extent;
			s0 = -(a01*s1 + b0);
			sqrDist = -s0*s0 + s1*(s1 + ((T)2)*b1) + c;
		}
	}
	else
	{
		// The line and segment are parallel.  Choose the closest pair so that
		// one point is at segment center.
		s1 = (T)0;
		s0 = -b0;
		sqrDist = b0*s0 + c;
	}

	mClosestPoint0 = mLine->origin + s0*mLine->direction;
	mClosestPoint1 = mSegment->center + s1*mSegment->direction;
	mLineParameter = s0;
	mSegmentParameter = s1;

	// Account for numerical round-off errors.
	if (sqrDist < (T)0)
	{
		sqrDist = (T)0;
	}
	return sqrDist;
}

template
class Line3Seg3Dist<float>;

template
class Line3Seg3Dist<double>;
