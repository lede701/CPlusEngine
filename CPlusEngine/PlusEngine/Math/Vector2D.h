#ifndef H_VECTOR2D
#define H_VECTOR2D

#include <string>
#include <memory>

namespace CPlusEngine{ namespace Math
{
	template<class T=float>
	class Vector2D
	{
	public:
		typedef std::unique_ptr<Vector2D<T>> Ptr;
	public:
		T x;
		T y;
		bool IsWorld;

		Vector2D();
		Vector2D(T ix, T iy, bool isWorld = true);

		virtual ~Vector2D();

		T Length() const;
		T LengthSqrd() const;

		Vector2D<T> Clone() const;

		virtual std::string ToString();

#pragma region Conversion Methods

		virtual Vector2D<int> ToInt();
		virtual Vector2D<float> ToFloat();

#pragma endregion

#pragma region Math Operators

		Vector2D<T> operator+(const Vector2D<T> &p2) const;
		Vector2D<T> operator-(const Vector2D<T> &p2) const;

		Vector2D<T> operator*(const Vector2D<T> &p2) const;
		// This can't be done according to http://physics.stackexchange.com/questions/111652/can-we-divide-two-vectors
		//Vector2D<T> operator/(const Vector2D<T> &p2) const;

		Vector2D<T> operator*(float scale) const;
		Vector2D<T> operator/(float scale) const;

		Vector2D<T> operator+(Ptr p2) const;
		Vector2D<T> operator-(Ptr p2) const;

#pragma endregion

#pragma region Math Equations

		Vector2D<T> Lerp(Ptr v1, float t);
		Vector2D<T> Lerp(Vector2D<T>* v1, float t);
		Vector2D<T> Normalized() const;

#pragma endregion

	};

} }// End namespace CPlusEngine::Math

#endif