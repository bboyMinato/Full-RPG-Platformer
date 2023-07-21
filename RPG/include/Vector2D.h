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
	Vector2D<T> operator+(const Vector2D<T>& v2) const
	{
		return Vector2D<T>(X + v2.X, Y + v2.Y);
	}

	//substraction
	Vector2D<T> operator-(const Vector2D<T>& v2) const
	{
		return Vector2D<T>(X - v2.X, Y - v2.Y);
	}

	//mupltiplication	
	Vector2D<T> operator*(const float scalar) const
	{
		return Vector2D<T>(X * scalar, Y * scalar);
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << "(X, Y) = (" << X << " " << Y << ")" << std::endl;
	}

private:
};

using Vector2Df = Vector2D<float>;