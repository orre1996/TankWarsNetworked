#pragma once

#include <vector>

struct vec2

{
	float x, y;
};

class Vec
{
public:
	Vec();
	~Vec();
	float Dot(vec2 a, vec2 b);
	float Length(vec2 a);
	vec2 Normalize(vec2 a);
};

