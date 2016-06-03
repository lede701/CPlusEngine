#pragma once
#include "Vector2D.h"
#include <sstream>

namespace CPlusEngine{ namespace Math
{
	template<class T>
	Vector2D<T>::Vector2D()
	{
		x = 0;
		y = 0;
		IsWorld = false;
	}

	template<class T>
	Vector2D<T>::Vector2D(T ix, T iy, bool isWorld/* = true*/)
	{
		x = ix;
		y = iy;
		IsWorld = isWorld;
	}

	template<class T>
	Vector2D<T>::~Vector2D()
	{
	}

	template<class T>
	T Vector2D<T>::Length() const
	{
		return sqrt(x*x + y*y);
	}

	template<class T>
	T Vector2D<T>::LengthSqrd() const
	{
		return x*x + y*y;
	}

	template<class T>
	Vector2D<T> Vector2D<T>::Clone() const
	{
		Vector2D<T> cl(x, y, IsWorld);
		return cl;
	}

	template<class T>
	std::string Vector2D<T>::ToString()
	{
		std::ostringstream out;
		out << (IsWorld ? "W" : "L" ) << " [" << x << ", " << y << "]";
		return out.str();
	}

#pragma region Math Operators

	template<class T>
	Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> &p2) const
	{
		return Vector2D<T>(x + p2.x, y + p2.y, IsWorld);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::operator-(const Vector2D<T> &p2) const
	{
		return Vector2D<T>(x - p2.x, y - p2.y, IsWorld);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::operator*(const Vector2D<T> &p2) const
	{
		// Definition of Dot Product between two vectors
		// x = v1.y * v2.z - v1.z * v2.y
		// y = v1.z * v2.x - v1.x * v2.z
		// z = v1.x * v2.y - v1.y * v2.x

		// Example numbers for v1(2,3,1), v2(4,5,1)
		// x = 3 * 1 - 1 * 5 = -2
		// y = 1 * 4 - 2 * 1 = 2
		// z = 2 * 5 - 3 * 4 = 3
		// new v = -2, 3, 3

		// Hypothisis: x = v1.y - v2.y, y = v2.x - v1.x
		// x = 3 - 5 = -2
		// y = 4 - 2 = 2

		// Need to perform the dot product of the vector on a 2D which is hard to find the equation
		return Vector2D<T>(y - p2.y, p2.x - x);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::operator*(float scale) const
	{
		return Vector2D<T>(x * scale, y * scale, IsWorld);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::operator/(float scale) const
	{
		return Vector2D<T>(x / scale, y / scale, IsWorld);
	}

#pragma endregion

#pragma region Math Equations

	template<class T>
	Vector2D<T> Vector2D<T>::Lerp(Ptr v1, float t)
	{
		// Lerp equation (1-t) * v0 + t * v1
		float lX = (1 - t)*x + t * v1->x;
		float lY = (1 - t)*y + t * v1->y;

		return Vector2D<T>(lX, lY, IsWorld);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::Lerp(Vector2D<T>* v1, float t)
	{
		// Lerp equation (1-t) * v0 + t * v1
		float lX = (1 - t)*x + t * v1->x;
		float lY = (1 - t)*y + t * v1->y;

		return Vector2D<T>(lX, lY, IsWorld);
	}

	template<class T>
	Vector2D<T> Vector2D<T>::Normalized() const
	{
		// Normilzed form is x / magnitude, y / magnitude also known as a unit vector
		return Vector2D<T>(x / Length(), y / Length(), IsWorld);
	}

#pragma endregion

#pragma region Conversion Methods

	template<class T>
	Vector2D<int> Vector2D<T>::ToInt()
	{
		Vector2D<int> conv(int(x), int(y), IsWorld);
		return conv;
	}

	template<class T>
	Vector2D<float> Vector2D<T>::ToFloat()
	{
		Vector2D<float> conv(float(x), float(y), IsWorld);
		return conv;
	}

#pragma endregion

} }// End namespace CPlusEngine::Math
