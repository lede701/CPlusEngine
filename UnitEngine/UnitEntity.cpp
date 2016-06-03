#include "stdafx.h"
#include "CppUnitTest.h"

#include <PlusEngine/Entity/Entity.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitEngine
{
	TEST_CLASS(UnitEntity)
	{
	public:
		typedef CPlusEngine::Entity::Entity Entity;
	public:
		
		TEST_METHOD(EntityClass)
		{
			Entity entity(5u);
			Assert::AreEqual(entity.Id(), 5u, L"Error ID didn't properly get set", LINE_INFO());
			Assert::AreEqual(entity.Position()->x, 0.f, L"Initial X Position is not set to 0", LINE_INFO());
			Assert::AreEqual(entity.Position()->y, 0.f, L"Initial Y Position is not set to 0", LINE_INFO());
			Assert::AreEqual(entity.Rotation()->x, 0.f, L"Initial X Position is not set to 0", LINE_INFO());
			Assert::AreEqual(entity.Rotation()->y, 0.f, L"Initial Y Position is not set to 0", LINE_INFO());
			Assert::AreEqual(entity.Scale()->x, 0.f, L"Initial X Position is not set to 0", LINE_INFO());
			Assert::AreEqual(entity.Scale()->y, 0.f, L"Initial Y Position is not set to 0", LINE_INFO());
		}

	};
}