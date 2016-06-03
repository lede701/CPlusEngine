#pragma once

#include "Rect2D.h"
#include <sstream>

namespace CPlusEngine{ namespace Math
{
	template<class T>
	Rect2D<T>::Rect2D()
	{
		x = static_cast<T>(0.0f);
		y = static_cast<T>(0.0f);
		w = static_cast<T>(0.0f);
		h = static_cast<T>(0.0f);
		IsWorld = false;
	}

	template<class T>
	Rect2D<T>::Rect2D(T ix, T iy, T iw, T ih, bool isWorld/* = true*/)
	{
		x = ix;
		y = iy;
		w = iw;
		h = ih;
		IsWorld = isWorld;
	}

	template<class T>
	Rect2D<T>::~Rect2D()
	{
	}

	template<class T>
	Rect2D<T> Rect2D<T>::Clone()
	{
		return Rect2D{ x, y, w, h, IsWorld };
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator+(const Rect2D<T> &r1) const
	{
		return Rect2D<T>(x + r1.x, y + r1.y, w + r1.w, h + r1.h, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator-(const Rect2D<T> &r1) const
	{
		return Rect2D<T>(x - r1.x, y - r1.y, w - r1.w, h - r1.h, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator*(const Rect2D<T> &r1) const
	{
		return Rect2D<T>(x * r1.x, y * r1.y, w * r1.w, h * r1.h, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator/(const Rect2D<T> &r1) const
	{
		return Rect2D<T>(x / r1.x, y / r1.y, w / r1.w, h / r1.h, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator+(float f) const
	{
		return Rect2D<T>(x + f, y + f, w + f, h + f, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator-(float f) const
	{
		return Rect2D<T>(x - f, y - f, w - f, h - f, IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator*(float f) const
	{
		return Rect2D<T>(T(x * f), T(y * f), T(w * f), T(h * f), IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::Resize(float f) const
	{
		return Rect2D<T>(x, y, T(w*f), T(h*f), IsWorld);
	}

	template<class T>
	Rect2D<T> Rect2D<T>::operator/(float f) const
	{
		return Rect2D<T>(x / f, y / f, w / f, h / f, IsWorld);
	}

	template<class T>
	std::string Rect2D<T>::ToString()
	{
		std::ostringstream out;
		out << "{" << (IsWorld ? 'W' : 'L') << x << ", " << y << ", " << w << ", " << h << "}";
		return out.str();
	}

	template<class T>
	Rect2D<int> Rect2D<T>::ToInt()
	{
		Rect2D<int> r(int(x), int(y), int(w), int(h), IsWorld);
		return r;
	}

	template<class T>
	Rect2D<float> Rect2D<T>::ToFloat()
	{
		Rect2D<float> r(float(x), float(y), float(w), float(h), IsWorld);
		return r;
	}

} }// End namespace CPlusEngine::Math
