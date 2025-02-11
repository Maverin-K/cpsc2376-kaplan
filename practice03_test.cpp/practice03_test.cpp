#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "practice03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Practice03Tests
{
    TEST_CLASS(MathUtilsTests)
    {
    public:
        // Tests for sumRange
        TEST_METHOD(SumRange_Normal)
        {
            Assert::AreEqual(10, MathUtils::sumRange(1, 5)); // 1+2+3+4
        }
        TEST_METHOD(SumRange_SingleValue)
        {
            Assert::AreEqual(0, MathUtils::sumRange(5, 5)); // Empty range
        }
        TEST_METHOD(SumRange_NegativeValues)
        {
            Assert::AreEqual(-6, MathUtils::sumRange(-3, 1)); // -3 + (-2) + (-1) + 0
        }

        // Tests for containsNegative
        TEST_METHOD(ContainsNegative_WithNegative)
        {
            std::vector<int> values = { 3, -1, 5, 7 };
            Assert::IsTrue(MathUtils::containsNegative(values));
        }
        TEST_METHOD(ContainsNegative_AllPositive)
        {
            std::vector<int> values = { 3, 1, 5, 7 };
            Assert::IsFalse(MathUtils::containsNegative(values));
        }
        TEST_METHOD(ContainsNegative_EmptyList)
        {
            std::vector<int> values = {};
            Assert::IsFalse(MathUtils::containsNegative(values));
        }

        // Tests for findMax
        TEST_METHOD(FindMax_Normal)
        {
            std::vector<int> values = { 3, 1, 5, 7 };
            Assert::AreEqual(7, MathUtils::findMax(values));
        }
        TEST_METHOD(FindMax_AllEqual)
        {
            std::vector<int> values = { 2, 2, 2, 2 };
            Assert::AreEqual(2, MathUtils::findMax(values));
        }
        TEST_METHOD(FindMax_EmptyList)
        {
            std::vector<int> values = {};
            Assert::AreEqual(0, MathUtils::findMax(values)); // Should handle empty case properly
        }
    };
}
