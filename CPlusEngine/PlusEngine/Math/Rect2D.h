#ifndef H_RECT2D
#define H_RECT2D

#include <memory>
#include <string>

namespace CPlusEngine{ namespace Math
{
	template<class T>
	class Rect2D
	{
	public:
		typedef std::unique_ptr<Rect2D<T>> Ptr;
		T x;
		T y;
		T w;
		T h;
		bool IsWorld;

		Rect2D();
		Rect2D(T ix, T iy, T iw, T ih, bool isWorld = true);

		virtual ~Rect2D();

		Rect2D<T> Clone();

		// Rect Math
		Rect2D<T> operator+(const Rect2D<T> &r1) const;
		Rect2D<T> operator-(const Rect2D<T> &r1) const;
		Rect2D<T> operator*(const Rect2D<T> &r1) const;
		Rect2D<T> operator/(const Rect2D<T> &r1) const;

		// Float math
		Rect2D<T> operator+(float f) const;
		Rect2D<T> operator-(float f) const;
		Rect2D<T> operator*(float f) const;
		Rect2D<T> Resize(float f) const;
		Rect2D<T> operator/(float f) const;

		// Utilities
		std::string ToString();

		// Converters
		Rect2D<int> ToInt();
		Rect2D<float> ToFloat();

	};

} }// End namespace CPlusEngine::Math

#endif