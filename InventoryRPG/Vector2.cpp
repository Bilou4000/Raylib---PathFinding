#include "Vector2.h"

#include <iomanip>
#include <sstream>

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

float Vec2::SqrDistance()
{
	return sqrt(x * x + y * y);
}

std::string Vec2::ToString()
{
	//Round float to .2f and convert it to string
	//for X
	std::stringstream xStream;
	xStream << std::fixed << std::setprecision(0) << x;
	std::string xPos = xStream.str();

	//for Y
	std::stringstream yStream;
	yStream << std::fixed << std::setprecision(0) << y;
	std::string yPos = yStream.str();

	return "(" + xPos + " , " + yPos + ")";

}

bool Vec2::operator==(const Vec2& goal) const
{
	return x == goal.x && y == goal.y;
}

Vec2 Vec2::operator-(const Vec2& vector2) const
{
	return Vec2(x - vector2.x, y - vector2.y);
}

Vec2 Vec2::operator+(const Vec2& vector2) const
{
	return Vec2(x + vector2.x, y + vector2.y);
}

