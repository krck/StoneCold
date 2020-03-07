
#include "pch.h"
#include "gtest/gtest.h"
#include "ArrayTP.hpp"

using StoneCold::Types::ArrayTP;

TEST(ArrayTP, ConstructDefault) {
	auto tdef = ArrayTP<int>(5);

	ASSERT_EQ(tdef.size(), 5);
	// assert: Heap Memory + 20 byte
}

TEST(ArrayTP, ConstructValue) {
	auto arr = ArrayTP<int>(5, 7);

	ASSERT_EQ(arr.size(), 5);
	ASSERT_EQ(arr[0], 7);
	// assert: Heap Memory + 20 byte
}

TEST(ArrayTP, ConstructCopy) {
	auto arr = ArrayTP<int>(5, 7);
	auto tcpy = ArrayTP<int>(arr);

	ASSERT_EQ(tcpy.size(), 5);
	ASSERT_EQ(tcpy[0], 7);
	// assert: Heap Memory + 20 byte
}

TEST(ArrayTP, ConstructMove) {
	auto tmov = ArrayTP<int>(std::move(ArrayTP<int>(5, 3)));

	ASSERT_EQ(tmov.size(), 5);
	ASSERT_EQ(tmov[0], 3);
	// assert: Heap Memory + 20 byte
}

TEST(ArrayTP, AssignmentCopy) {
	auto tasign1 = ArrayTP<int>(10, 2);
	auto tasign2 = ArrayTP<int>(20, 5);

	tasign1 = tasign2;
	ASSERT_EQ(tasign1.size(), tasign2.size());
	ASSERT_EQ(tasign1[0], tasign2[0]);
	// assert: Heap Memory + 40 byte
}

TEST(ArrayTP, AssignmentMove) {
	auto tasign1 = ArrayTP<int>(10, 2);
	auto tasign2 = ArrayTP<int>(20, 5);

	tasign1 = std::move(tasign2);
	ASSERT_EQ(tasign1.size(), tasign2.size());
	ASSERT_EQ(tasign1[0], tasign2[0]);
	// assert: Heap Memory + 40 byte
}

TEST(ArrayTP, AccessRandom) {
	auto arr = ArrayTP<int>(20, 123);

	auto aVal1 = arr[10];
	const auto aVal2 = arr[15];
	auto aVal3 = arr[30];

	EXPECT_EQ(aVal1, 123);
	EXPECT_EQ(aVal2, 123);
	EXPECT_NE(aVal3, 123);
}

TEST(ArrayTP, AccessAt) {
	auto arr = ArrayTP<int>(20, 123);

	auto aVal1 = arr.at(10);
	const auto aVal2 = arr.at(15);

	bool hasThrown = false;
	try { int& aVal3 = arr.at(30); }
	catch (const std::exception & e) { hasThrown = true; }

	EXPECT_EQ(aVal1, 123);
	EXPECT_EQ(aVal2, 123);
	EXPECT_EQ(hasThrown, true) << ".at() failed throw on out of bounds access";
}

TEST(ArrayTP, Size) {
	auto arr = ArrayTP<int>(20, 123);
	auto tsize = arr.size();

	ASSERT_EQ(tsize, 20);
}

TEST(ArrayTP, Empty) {
	auto tnempt = ArrayTP<int>(10).empty();
	auto tempt = ArrayTP<int>(0).empty();

	ASSERT_EQ(tnempt, false);
	ASSERT_EQ(tempt, true);
}

TEST(ArrayTP, Insert) {
	int iVal = 123;
	auto arr = ArrayTP<int>(20, 0);
	arr.insert(1, iVal);
	arr.insert(2, 321);

	ASSERT_EQ(arr[1], iVal) << "failed to copy insert() a value";
	ASSERT_EQ(arr[2], 321) << "failed to move insert() a value";
}

TEST(ArrayTP, Erase) {
	auto arr = ArrayTP<int>(20, 123);
	arr.erase(2);

	ASSERT_EQ(arr[2], 0) << "failed to erase() a value";
}

TEST(ArrayTP, Compare) {
	auto arr1 = ArrayTP<int>(20, 123);
	auto arr2 = ArrayTP<int>(20, 123);

	auto comp1 = arr1 == arr2;
	auto comp2 = arr1 != arr2;

	ASSERT_EQ(comp1, true);
	ASSERT_EQ(comp2, false);
}
