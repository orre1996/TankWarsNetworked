//#include "stdafx.h"
#include "Vec.h"


Vec::Vec()
{
}


Vec::~Vec()
{
}

float Vec::Dot(vec2 a, vec2 b)
{

	return a.x * b.x + a.y * b.y;
}

float Vec::Length(vec2 a)
{
	return sqrt(Dot(a, a));
}

vec2 Vec::Normalize(vec2 a)
{
	vec2 normalizeVec = { 0,0 };
	float x = 0.0f;
	float y = 0.0f;
	if (a.x != 0)
	{
		x = a.x / Length(a);
	}
	if (a.y != 0)
	{
		y = a.y / Length(a);
	}
	normalizeVec = { x,  y };
	return normalizeVec;
}
