
template<>
TriangleKey<true>::TriangleKey(int v0, int v1, int v2)
{
	if (v0 < v1)
	{
		if (v0 < v2)
		{
			// v0 is minimum
			V[0] = v0;
			V[1] = v1;
			V[2] = v2;
		}
		else
		{
			// v2 is minimum
			V[0] = v2;
			V[1] = v0;
			V[2] = v1;
		}
	}
	else
	{
		if (v1 < v2)
		{
			// v1 is minimum
			V[0] = v1;
			V[1] = v2;
			V[2] = v0;
		}
		else
		{
			// v2 is minimum
			V[0] = v2;
			V[1] = v0;
			V[2] = v1;
		}
	}
}

template<>
TriangleKey<false>::TriangleKey(int v0, int v1, int v2)
{
	if (v0 < v1)
	{
		if (v0 < v2)
		{
			// v0 is minimum
			V[0] = v0;
			V[1] = std::min(v1, v2);
			V[2] = std::max(v1, v2);
		}
		else
		{
			// v2 is minimum
			V[0] = v2;
			V[1] = std::min(v0, v1);
			V[2] = std::max(v0, v1);
		}
	}
	else
	{
		if (v1 < v2)
		{
			// v1 is minimum
			V[0] = v1;
			V[1] = std::min(v2, v0);
			V[2] = std::max(v2, v0);
		}
		else
		{
			// v2 is minimum
			V[0] = v2;
			V[1] = std::min(v0, v1);
			V[2] = std::max(v0, v1);
		}
	}
}
