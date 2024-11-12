#include "pch.h"
#include "CppUnitTest.h"
#include "../10.2 В/102.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student students[3];

			students[0].lastName = "Strogan";
			students[0].course = 2;
			students[0].speciality = ComputerScience;
			students[0].grades.physics = 5;
			students[0].grades.math = 5;
			students[0].grades.programming = 5;

			students[1].lastName = "Kotovych";
			students[1].course = 3;
			students[1].speciality = Informatics;
			students[1].grades.physics = 4;
			students[1].grades.math = 4;
			students[1].grades.numericalMethods = 4;

			students[2].lastName = "Stefurak";
			students[2].course = 2;
			students[2].speciality = MathAndEconomics;
			students[2].grades.physics = 4;
			students[2].grades.math = 5;
			students[2].grades.pedagogy = 5;

			int indexArray[3];
			IndexSort(students, indexArray, 3);

			int foundIdx = BinarySearch(students, indexArray, 3, "Strogan", 2, 5);
			Assert::AreEqual(0, foundIdx);

		}
	};
}
