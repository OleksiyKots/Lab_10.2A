#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(StudentTests)
    {
    public:

        TEST_METHOD(TestSortStudents)
        {
            // Arrange
            Student students[3] = {
                {"Ivanov", 1, KOMPYUTERNI_NAUKY, 80, 85, 90},
                {"Petrenko", 2, INFORMATYKA, 70, 75, 80},
                {"Shevchenko", 1, MATEMATYKA_TA_EKONOMIKA, 85, 90, 95}
            };

            // Act
            SortStudents(students, 3);

            // Assert
            Assert::AreEqual(students[0].prizv, string("Ivanov"));
            Assert::AreEqual(students[1].prizv, string("Petrenko"));
            Assert::AreEqual(students[2].prizv, string("Shevchenko"));
        }

        TEST_METHOD(TestBinarySearch)
        {
            // Arrange
            Student students[3] = {
                {"Ivanov", 1, KOMPYUTERNI_NAUKY, 80, 85, 90},
                {"Petrenko", 2, INFORMATYKA, 70, 75, 80},
                {"Shevchenko", 1, MATEMATYKA_TA_EKONOMIKA, 85, 90, 95}
            };
            SortStudents(students, 3); // Ensure sorted before binary search

            // Act & Assert
            int index = BinarySearch(students, 3, "Petrenko");
            Assert::AreEqual(index, 1); // Petrenko should be at index 1

            index = BinarySearch(students, 3, "Nonexistent");
            Assert::AreEqual(index, -1); // Nonexistent should not be found
        }
    };
}
