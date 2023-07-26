#pragma once
#include <iostream>
#include <string>

template<typename T>
class Vector2D
{
public:
	T X, Y;

	Vector2D(T x = 0, T y = 0) : X(x), Y(y) {}

	//addition
	inline Vector2D<T> operator+(const Vector2D<T>& v2) const
	{
		return Vector2D<T>(X + v2.X, Y + v2.Y);
	}

	//substraction
	inline Vector2D<T> operator-(const Vector2D<T>& v2) const
	{
		return Vector2D<T>(X - v2.X, Y - v2.Y);
	}

	//mupltiplication	
	inline Vector2D<T> operator*(const float scalar) const
	{
		return Vector2D<T>(X * scalar, Y * scalar);
	}

	inline Vector2D<T>& Zero()
	{
		X = 0;
		Y = 0;
		return *this;
	}

	inline Vector2D<T>& One()
	{
		X = 1;
		Y = 1;
		return *this;
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << "(X, Y) = (" << X << " " << Y << ")" << std::endl;
	}

private:
};

using Vector2Di = Vector2D<int>;
using Vector2Df = Vector2D<float>;
