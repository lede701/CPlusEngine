#include "stdafx.h"
#include "CppUnitTest.h"
#include <Math\Vector2D.h>
#include <Math\Vector2D.cpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPlusUnits
{	
	TEST_CLASS(UnitVector2D)
	{
	public:
		
		TEST_METHOD(Vector2D)
		{
			using CPlusEngine::Math::Vector2D;
			// Test a simple 3,4,5 triangle vector
			Vector2D v(3, 4);
			Assert::AreEqual(v.Length(), 5.0f, L"Error length is not 5", LINE_INFO());
			Assert::AreEqual(v.LengthSqrd(), 25.0f, L"Error squared length is not 25", LINE_INFO());

			// Test normalizing the vetor
			Vector2D norm = v.Normalized();
			Assert::AreEqual(norm.Length(), 1.0f, L"The vector did not normalize", LINE_INFO());
			// Validate the data hasn't changed in original vector
			Assert::AreEqual(v.x, 3.0f, L"Normal vector.x change original value", LINE_INFO());
			Assert::AreEqual(v.y, 4.0f, L"Normal vector.y change original value", LINE_INFO());

			// Test vector addition
			Vector2D v2(1, 1);
			Vector2D p = v + v2;
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
			Assert::AreEqual(p.x, 5.0f, L"5.0 x 1.0 doesn't equal 5.0", LINE_INFO());
			Assert::AreEqual(p.y, 0.0f, L"5.0 x 0.0 doesn't equal 0.0", LINE_INFO());

			// Here is a fun one
			v.x = 1.0f;
			v.y = 1.0f;
			// What is the square root of 2?
			Assert::AreEqual(v.Length(), 1.41421f, L"Square root of 2 doesn't match 1.41421", LINE_INFO());
		}

	};
}