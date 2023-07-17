#pragma once

class Point
{
public:
	float X, Y;

	Point(float X = 0, float Y = 0) : X(X), Y(Y) {}


	//addition +
	inline Point operator+(const Point& p2) const
	{
		return Point(X + p2.X, Y + p2.Y);
	}

	//addition +=
	inline friend Point operator+=(Point& p1, const Point& p2)
	{
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}

	//substraction -
	inline Point operator -(const Point& p2) const
	{
		return Point(X - p2.X, Y - p2.Y);
	}

	//substraction -=
	inline friend Point operator-=(Point& p1, const Point& p2)
	{
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	//multiplication	
	inline Point operator*(const float scalar) const
	{
		return Point(X * scalar, Y * scalar);
	}
};