#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP6.4/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Arrange
			Matrix<int> A{ {1, 2, 3}, {4, 5, 6} };
			Matrix<int> B{ {1, 2, 3}, {4, 5, 6} };
			// Act
			int expected = 2;
			// Assert
			Assert::AreEqual(expected, 2);
		}
	};
}
