#pragma once

#include <string>

struct Vec2
{
	Vec2(float x = 0, float y = 0);

	float SqrDistance();
	std::string ToString();

	bool operator==(const Vec2& goal) const;
	Vec2 operator-(const Vec2& vector2) const;
	Vec2 operator+(const Vec2& vector2) const;

	float x, y;
};

