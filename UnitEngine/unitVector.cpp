#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPlusUnits
{
	TEST_CLASS(UnitMath)
	{
	public:

		TEST_METHOD(Vector)
		{
			// Test a simple 3,4,5 triangle vector
			fVector2D v(3.f, 4.f);
			Assert::AreEqual(v.Length(), 5.0f, L"Error length is not 5", LINE_INFO());
			Assert::AreEqual(v.LengthSqrd(), 25.0f, L"Error squared length is not 25", LINE_INFO());

			// Test normalizing the vetor
			fVector2D norm = v.Normalized();
			Assert::AreEqual(norm.Length(), 1.0f, L"The vector did not normalize", LINE_INFO());
			// Validate the data hasn't changed in original vector
			Assert::AreEqual(v.x, 3.0f, L"Normal vector.x change original value", LINE_INFO());
			Assert::AreEqual(v.y, 4.0f, L"Normal vector.y change original value", LINE_INFO());

			// Test vector addition
			fVector2D v2(1, 1);
			fVector2D p = v + v2;
			Assert::AreEqual(p.x, 4.0f, L"Vectors v.x + v2.x did not add up to 4", LINE_INFO());
			Assert::AreEqual(p.y, 5.0f, L"Vectors v.y + v2.y did not add up to 5", LINE_INFO());

			// Test vector subtration
			p = v - v2;
			Assert::AreEqual(p.x, 2.0f, L"Vectors v.x + v2.x did not subtract to 2", LINE_INFO());
			Assert::AreEqual(p.y, 3.0f, L"Vectors v.y + v2.y did not subtract to 3", LINE_INFO());

			// Test vector multiplication
			p = v * 2;
			Assert::AreEqual(p.x, 6.0f, L"Vectors v.x * 2 did not multiply to 6", LINE_INFO());
			Assert::AreEqual(p.y, 8.0f, L"Vectors v.x * 2 did not multiply to 10", LINE_INFO());

			// Test vector division
			p = v / 2;
			Assert::AreEqual(p.x, 1.5f, L"Vectors v.x / 2 did not divide to 1.5", LINE_INFO());
			Assert::AreEqual(p.y, 2.0f, L"Vectors v.x / 2 did not divide to 2", LINE_INFO());

			// Test a simple 1 unit vector
			v.x = 1.0f;
			v.y = 0.0f;
			norm = v.Normalized();
			Assert::AreEqual(norm.Length(), 1.0f, L"Length of vector 1,0 should be 1", LINE_INFO());
			Assert::AreEqual(norm.LengthSqrd(), 1.0f, L"LengthSqrd of vector 1,0 should be 1", LINE_INFO());

			// Test vector multiplication on a 1 unit vector
			p = v * 5.0f;
			Assert::AreEqual(5.0f, p.x, L"5.0 x 1.0 doesn't equal 5.0", LINE_INFO());
			Assert::AreEqual(0.0f, p.y, L"5.0 x 0.0 doesn't equal 0.0", LINE_INFO());

			// Here is a fun one
			v.x = 1.0f;
			v.y = 1.0f;
			// What is the square root of 2?
			//Assert::AreEqual(1.41421f, v.Length(), L"Square root of 2 doesn't match 1.41421", LINE_INFO());
		}

		TEST_METHOD(Rect)
		{
			using CPlusEngine::Math::Rect2D;

			fRect2D r;

			// Check to make sure r is properly set
			Assert::AreEqual(0.0f, r.x, L"Rect x is not properly set to 0.0f", LINE_INFO());
			Assert::AreEqual(0.0f, r.y, L"Rect y is not properly set to 0.0f", LINE_INFO());
			Assert::AreEqual(0.0f, r.w, L"Rect w is not properly set to 0.0f", LINE_INFO());
			Assert::AreEqual(0.0f, r.h, L"Rect h is not properly set to 0.0f", LINE_INFO());

			// All sides equal
			float rbox = 1.0f;
			fRect2D r2(rbox, rbox, rbox, rbox);
			Assert::AreEqual(rbox, r2.x, L"Rect x is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(rbox, r2.y, L"Rect y is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(rbox, r2.w, L"Rect w is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(rbox, r2.h, L"Rect h is not properly set to rbox", LINE_INFO());

			// All different values
			fRect2D r3(1.0f, 2.0f, 3.0f, 4.0f);
			Assert::AreEqual(1.0f, r3.x, L"Rect x is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(2.0f, r3.y, L"Rect y is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(3.0f, r3.w, L"Rect w is not properly set to rbox", LINE_INFO());
			Assert::AreEqual(4.0f, r3.h, L"Rect h is not properly set to rbox", LINE_INFO());

		}

	};
}