
#include "pch.h"
#include "gtest/gtest.h"
#include "EntityComponentArray.hpp"

using StoneCold::Engine::EntityComponentArray;

struct TestComponent {
	int a, b;
	TestComponent() : a(0), b(0) {}
	TestComponent(int ap, int bp) : a(ap), b(bp) {}
};

//
// Test the EntityComponentArrays construction with a size parameter
//
TEST(EntityComponentArray, ConstructDefaultAndMaxSize) {
	auto arr = EntityComponentArray<TestComponent>(5);

	ASSERT_EQ(arr.max_size(), 5);
	// assert: Heap Memory + 20 byte
}

//
// Test the EntityComponentArrays random access operator (non-const / const)
//
TEST(EntityComponentArray, AccessRandom) {
	auto arr = EntityComponentArray<TestComponent>(20);
	auto defC = TestComponent();

	auto aVal1 = arr[10];
	const auto aVal2 = arr[15];
	auto aVal3 = arr[30];

	EXPECT_EQ(aVal1.a, defC.a);
	EXPECT_EQ(aVal2.a, defC.a);
	EXPECT_NE(aVal3.a, defC.a);
}

//
// Test the EntityComponentArrays at() access operator (non-const / const)
//
TEST(EntityComponentArray, AccessAt) {
	auto arr = EntityComponentArray<TestComponent>(20);
	auto defC = TestComponent();

	auto aVal1 = arr.at(10);
	const auto aVal2 = arr.at(15);

	bool hasThrown = false;
	try { auto aVal3 = arr.at(30); }
	catch (const std::out_of_range& oor) { hasThrown = true; }

	EXPECT_EQ(aVal1.a, defC.a);
	EXPECT_EQ(aVal2.a, defC.a);
	EXPECT_EQ(hasThrown, true) << ".at() failed throw on out of bounds access";
}

//
// Test the EntityComponentArrays insert() function (size changes)
//
TEST(EntityComponentArray, InsertSizeEmpty) {
	auto arr = EntityComponentArray<TestComponent>(3);

	EXPECT_EQ(arr.max_size(), 3);
	EXPECT_EQ(arr.size(), 0);
	EXPECT_EQ(arr.empty(), true);
	EXPECT_EQ(arr.GetEntityIndexMap().size(), 0);

	auto i1 = arr.insert(10, TestComponent(100, 100));
	auto i2 = arr.insert(20, TestComponent(200, 200));
	auto i3 = arr.insert(30, TestComponent(300, 300));
	auto i4 = arr.insert(40, TestComponent(400, 400));

	EXPECT_EQ(i1, true);
	EXPECT_EQ(i2, true);
	EXPECT_EQ(i3, true);
	EXPECT_EQ(i4, false) << "Failed to check out of bounds insert";

	ASSERT_EQ(arr.max_size(), 3);
	ASSERT_EQ(arr.size(), 3);
	ASSERT_EQ(arr.empty(), false);
	ASSERT_EQ(arr.GetEntityIndexMap().size(), 3);
}

//
// Test the EntityComponentArrays insert() function (copy / move insert)
//
TEST(EntityComponentArray, InsertCopyMove) {
	auto arr = EntityComponentArray<TestComponent>(3);

	auto iVal = TestComponent(100, 100);
	arr.insert(10, iVal);
	arr.insert(20, TestComponent(200, 200));

	ASSERT_EQ(arr[1].a, iVal.a) << "Failed to copy insert() a value";
	ASSERT_EQ(arr[2].b, TestComponent(200, 200).b) << "Failed to move insert() a value";
}

//
// Test the EntityComponentArrays insert() function (index mapping and array value placement)
//
TEST(EntityComponentArray, InsertIndexCheck) {
	auto arr = EntityComponentArray<TestComponent>(3);

	arr.insert(10, TestComponent(100, 100));
	arr.insert(20, TestComponent(200, 200));
	arr.insert(30, TestComponent(300, 300));
	arr.insert(40, TestComponent(400, 400));

	// Check if the used memory is continuous
	//EXPECT_EQ((int)&arr.GetRawData()[1], (int)&arr.GetRawData()[0] + sizeof(TestComponent));
	//EXPECT_EQ((int)&arr.GetRawData()[2], (int)&arr.GetRawData()[1] + sizeof(TestComponent));

	// Check if the correct indices were generated
	auto indexE10 = arr.GetEntityIndexMap().find(10)->second;
	auto indexE20 = arr.GetEntityIndexMap().find(20)->second;
	auto indexE30 = arr.GetEntityIndexMap().find(30)->second;
	ASSERT_EQ(indexE10, 0) << "Unexprected Index mapping after insert";
	ASSERT_EQ(indexE20, 1) << "Unexprected Index mapping after insert";
	ASSERT_EQ(indexE30, 2) << "Unexprected Index mapping after insert";
	ASSERT_EQ(arr.GetEntityIndexMap().find(40), arr.GetEntityIndexMap().end()) << "Unexprected Index after out of bounds insert";

	// Check if the indices access the correct values
	ASSERT_EQ(arr.GetRawData()[indexE10].a, 100) << "Unexprected Index array-access result";
	ASSERT_EQ(arr.GetRawData()[indexE20].a, 200) << "Unexprected Index array-access result";
	ASSERT_EQ(arr.GetRawData()[indexE30].a, 300) << "Unexprected Index array-access result";
}

//
// Test the EntityComponentArrays insert() function (replace existing value)
//
TEST(EntityComponentArray, InsertReplace) {
	auto arr = EntityComponentArray<TestComponent>(3);

	arr.insert(10, TestComponent(100, 100));
	auto index1 = arr.GetEntityIndexMap().find(10)->second;
	EXPECT_EQ(index1, 0) << "Unexprected Index mapping after insert";
	EXPECT_EQ(arr.GetRawData()[index1].a, 100) << "Unexprected Index array-access result";

	// Index mapping must stay the same, only data array needs to change
	arr.insert(10, TestComponent(200, 200));
	auto index2 = arr.GetEntityIndexMap().find(10)->second;
	EXPECT_EQ(index2, 0) << "Unexprected Index mapping after insert";
	EXPECT_EQ(arr.GetRawData()[index2].a, 200) << "Unexprected Index array-access result";
}

//
// Test the EntityComponentArrays erase() function (size changes)
//
TEST(EntityComponentArray, EraseSizeEmpty) {
	auto arr = EntityComponentArray<TestComponent>(3);

	arr.insert(10, TestComponent(100, 100));
	arr.insert(20, TestComponent(200, 200));

	EXPECT_EQ(arr.max_size(), 3);
	EXPECT_EQ(arr.GetRawData()[0].a, 100);
	EXPECT_EQ(arr.GetRawData()[1].a, 200);
	EXPECT_EQ(arr.empty(), false);
	EXPECT_EQ(arr.size(), 2);

	arr.erase(10);

	EXPECT_EQ(arr.max_size(), 3);
	EXPECT_EQ(arr.GetRawData()[0].a, 200);
	EXPECT_EQ(arr.GetRawData()[1].a, 0);
	ASSERT_EQ(arr.empty(), false);
	ASSERT_EQ(arr.size(), 1) << "Failed to reduce the array size after erase()";

	arr.erase(20);

	EXPECT_EQ(arr.max_size(), 3);
	EXPECT_EQ(arr.GetRawData()[0].a, 0);
	EXPECT_EQ(arr.GetRawData()[1].a, 0);
	ASSERT_EQ(arr.empty(), true) << "Failed to reduce the array size after erase()";
	ASSERT_EQ(arr.size(), 0) << "Failed to reduce the array size after erase()";
}

//
// Test the EntityComponentArrays erase() function (index mapping and array value placement)
//
TEST(EntityComponentArray, Erase) {
	auto arr = EntityComponentArray<TestComponent>(5);

	arr.insert(10, TestComponent(100, 100));
	arr.insert(20, TestComponent(200, 200));
	arr.insert(30, TestComponent(300, 300));
	arr.insert(40, TestComponent(400, 400));
	arr.insert(50, TestComponent(500, 500));

	ASSERT_EQ(arr.size(), 5);

	// Check if the correct indices were generated and the array values were added accordingly
	auto indexE10 = arr.GetEntityIndexMap().find(10)->second;
	auto indexE20 = arr.GetEntityIndexMap().find(20)->second;
	auto indexE30 = arr.GetEntityIndexMap().find(30)->second;
	auto indexE40 = arr.GetEntityIndexMap().find(40)->second;
	auto indexE50 = arr.GetEntityIndexMap().find(50)->second;
	EXPECT_EQ(indexE10, 0) << "Unexprected Index mapping after insert";
	EXPECT_EQ(indexE20, 1) << "Unexprected Index mapping after insert";
	EXPECT_EQ(indexE30, 2) << "Unexprected Index mapping after insert";
	EXPECT_EQ(indexE40, 3) << "Unexprected Index mapping after insert";
	EXPECT_EQ(indexE50, 4) << "Unexprected Index mapping after insert";
	EXPECT_EQ(arr.GetRawData()[indexE10].a, 100) << "Unexprected Index array-access result";
	EXPECT_EQ(arr.GetRawData()[indexE20].a, 200) << "Unexprected Index array-access result";
	EXPECT_EQ(arr.GetRawData()[indexE30].a, 300) << "Unexprected Index array-access result";
	EXPECT_EQ(arr.GetRawData()[indexE40].a, 400) << "Unexprected Index array-access result";
	EXPECT_EQ(arr.GetRawData()[indexE50].a, 500) << "Unexprected Index array-access result";

	// Now remove from the middle
	arr.erase(20);

	// Entity 20 must be replaced with the last position and the last position must be empty now
	auto eIndex1 = arr.GetEntityIndexMap().find(20);
	auto eIndex2 = arr.GetEntityIndexMap().find(50);
	ASSERT_EQ(eIndex1, arr.GetEntityIndexMap().end()) << "Failed to remove index mapping";
	ASSERT_EQ(eIndex2->second, 1) << "Failed to update index mapping";

	ASSERT_EQ(arr.GetRawData()[1].a, 500) << "Failed to swap array values";
	ASSERT_EQ(arr.GetRawData()[4].a, 0) << "Failed to clear last array value";
}

//
// Test the EntityComponentArrays erase() function (erase non existent element)
//
TEST(EntityComponentArray, EraseNotExistent) {
	auto arr = EntityComponentArray<TestComponent>(5);
	arr.insert(10, TestComponent(100, 100));

	auto eResult1 = arr.erase(10);
	auto eResult2 = arr.erase(12314);

	ASSERT_EQ(eResult1, true);
	ASSERT_EQ(eResult2, false);
}
