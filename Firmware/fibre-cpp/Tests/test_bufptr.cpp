/**
 * @file test_bufptr.cpp
 * @brief Unit tests for generic_bufptr_t template class
 * 
 * Tests buffer pointer wrapper functionality including construction,
 * iteration, manipulation, and edge cases.
 * 
 * @author ODrive Robotics
 * @date 2026-01-14
 */

#include <gtest/gtest.h>
#include <fibre/bufptr.hpp>
#include <vector>
#include <algorithm>

using namespace fibre;

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(BufptrTest, ConstructorFromPointerAndLength) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    EXPECT_EQ(10, buf.size());
    EXPECT_EQ(data, buf.begin());
    EXPECT_EQ(data + 10, buf.end());
}

TEST(BufptrTest, ConstructorFromPointerRange) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, data + 10);
    
    EXPECT_EQ(10, buf.size());
    EXPECT_EQ(data, buf.begin());
    EXPECT_EQ(data + 10, buf.end());
}

TEST(BufptrTest, DefaultConstructor) {
    bufptr_t buf;
    
    EXPECT_EQ(0, buf.size());
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(nullptr, buf.begin());
    EXPECT_EQ(nullptr, buf.end());
}

TEST(BufptrTest, ConstructorFromArray) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data);
    
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(data, buf.begin());
}

TEST(BufptrTest, ConstructorFromVector) {
    std::vector<unsigned char> vec = {10, 20, 30, 40};
    bufptr_t buf(vec);
    
    EXPECT_EQ(4, buf.size());
    EXPECT_EQ(vec.data(), buf.begin());
}

TEST(BufptrTest, ConstructorFromConstVector) {
    const std::vector<unsigned char> vec = {10, 20, 30, 40};
    cbufptr_t buf(vec);
    
    EXPECT_EQ(4, buf.size());
    EXPECT_EQ(vec.data(), buf.begin());
}

TEST(BufptrTest, CopyConstructorNonConstToConst) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf1(data, 5);
    cbufptr_t buf2(buf1);
    
    EXPECT_EQ(buf1.size(), buf2.size());
    EXPECT_EQ(buf1.begin(), buf2.begin());
}

// ============================================================================
// Size and Empty Tests
// ============================================================================

TEST(BufptrTest, SizeOfEmptyBuffer) {
    bufptr_t buf;
    EXPECT_EQ(0, buf.size());
}

TEST(BufptrTest, SizeOfNonEmptyBuffer) {
    unsigned char data[100];
    bufptr_t buf(data, 100);
    EXPECT_EQ(100, buf.size());
}

TEST(BufptrTest, EmptyReturnsTrueForZeroSize) {
    bufptr_t buf;
    EXPECT_TRUE(buf.empty());
}

TEST(BufptrTest, EmptyReturnsFalseForNonZeroSize) {
    unsigned char data[1] = {0};
    bufptr_t buf(data, 1);
    EXPECT_FALSE(buf.empty());
}

// ============================================================================
// Iterator Tests
// ============================================================================

TEST(BufptrTest, IteratorBeginEnd) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    EXPECT_EQ(data, buf.begin());
    EXPECT_EQ(data + 5, buf.end());
}

TEST(BufptrTest, RangeBasedForLoop) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    size_t index = 0;
    for (auto& byte : buf) {
        EXPECT_EQ(data[index], byte);
        ++index;
    }
    EXPECT_EQ(5, index);
}

TEST(BufptrTest, StandardAlgorithmWithIterators) {
    unsigned char data[5] = {5, 2, 8, 1, 9};
    bufptr_t buf(data, 5);
    
    auto max_element = std::max_element(buf.begin(), buf.end());
    EXPECT_EQ(9, *max_element);
}

// ============================================================================
// Access Operators
// ============================================================================

TEST(BufptrTest, DereferenceOperator) {
    unsigned char data[5] = {42, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    EXPECT_EQ(42, *buf);
}

TEST(BufptrTest, IndexOperator) {
    unsigned char data[5] = {10, 20, 30, 40, 50};
    bufptr_t buf(data, 5);
    
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(30, buf[2]);
    EXPECT_EQ(50, buf[4]);
}

TEST(BufptrTest, IndexOperatorModification) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    buf[2] = 99;
    EXPECT_EQ(99, data[2]);
    EXPECT_EQ(99, buf[2]);
}

TEST(BufptrTest, FrontAccess) {
    unsigned char data[5] = {100, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    EXPECT_EQ(100, buf.front());
}

TEST(BufptrTest, BackAccess) {
    unsigned char data[5] = {1, 2, 3, 4, 200};
    bufptr_t buf(data, 5);
    
    EXPECT_EQ(200, buf.back());
}

// ============================================================================
// Compound Assignment Operator Tests
// ============================================================================

TEST(BufptrTest, CompoundAdditionOperator) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    buf += 3;
    
    EXPECT_EQ(7, buf.size());
    EXPECT_EQ(data + 3, buf.begin());
    EXPECT_EQ(3, *buf);
}

TEST(BufptrTest, CompoundAdditionBeyondEnd) {
    unsigned char data[5] = {0, 1, 2, 3, 4};
    bufptr_t buf(data, 5);
    
    buf += 10;  // Beyond size - should clamp
    
    EXPECT_EQ(0, buf.size());
    EXPECT_TRUE(buf.empty());
}

TEST(BufptrTest, CompoundAdditionZero) {
    unsigned char data[5] = {0, 1, 2, 3, 4};
    bufptr_t buf(data, 5);
    
    buf += 0;
    
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(data, buf.begin());
}

TEST(BufptrTest, PostIncrementOperator) {
    unsigned char data[5] = {10, 20, 30, 40, 50};
    bufptr_t buf(data, 5);
    
    bufptr_t old = buf++;
    
    // Old buffer should have original state
    EXPECT_EQ(5, old.size());
    EXPECT_EQ(10, *old);
    
    // New buffer should be advanced
    EXPECT_EQ(4, buf.size());
    EXPECT_EQ(20, *buf);
}

// ============================================================================
// Take Method Tests
// ============================================================================

TEST(BufptrTest, TakeNormalCase) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    auto taken = buf.take(5);
    
    EXPECT_EQ(5, taken.size());
    EXPECT_EQ(data, taken.begin());
    EXPECT_EQ(data + 5, taken.end());
    
    // Original should be unchanged
    EXPECT_EQ(10, buf.size());
}

TEST(BufptrTest, TakeZeroBytes) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto taken = buf.take(0);
    
    EXPECT_EQ(0, taken.size());
    EXPECT_TRUE(taken.empty());
}

TEST(BufptrTest, TakeAllBytes) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto taken = buf.take(5);
    
    EXPECT_EQ(5, taken.size());
    EXPECT_EQ(buf.begin(), taken.begin());
}

TEST(BufptrTest, TakeMoreThanAvailable) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto taken = buf.take(10);  // More than size
    
    // Should clamp to available size
    EXPECT_EQ(5, taken.size());
}

// ============================================================================
// Skip Method Tests
// ============================================================================

TEST(BufptrTest, SkipNormalCase) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    auto skipped = buf.skip(3);
    
    EXPECT_EQ(7, skipped.size());
    EXPECT_EQ(data + 3, skipped.begin());
    EXPECT_EQ(data + 10, skipped.end());
    
    // Original should be unchanged
    EXPECT_EQ(10, buf.size());
}

TEST(BufptrTest, SkipWithProcessedBytesCounter) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    size_t processed = 0;
    
    auto skipped = buf.skip(4, &processed);
    
    EXPECT_EQ(4, processed);
    EXPECT_EQ(6, skipped.size());
}

TEST(BufptrTest, SkipMultipleTimesWithCounter) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    size_t processed = 0;
    
    auto skip1 = buf.skip(2, &processed);
    auto skip2 = skip1.skip(3, &processed);
    
    EXPECT_EQ(5, processed);
    EXPECT_EQ(5, skip2.size());
    EXPECT_EQ(data + 5, skip2.begin());
}

TEST(BufptrTest, SkipZeroBytes) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto skipped = buf.skip(0);
    
    EXPECT_EQ(5, skipped.size());
    EXPECT_EQ(buf.begin(), skipped.begin());
}

TEST(BufptrTest, SkipAllBytes) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto skipped = buf.skip(5);
    
    EXPECT_EQ(0, skipped.size());
    EXPECT_TRUE(skipped.empty());
}

TEST(BufptrTest, SkipMoreThanAvailable) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    auto skipped = buf.skip(10);
    
    // Should clamp to available size
    EXPECT_EQ(0, skipped.size());
    EXPECT_TRUE(skipped.empty());
}

// ============================================================================
// Combined Operations Tests
// ============================================================================

TEST(BufptrTest, TakeAndSkipCombination) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    auto first = buf.take(3);   // [0, 1, 2]
    auto rest = buf.skip(3);    // [3, 4, 5, 6, 7, 8, 9]
    
    EXPECT_EQ(3, first.size());
    EXPECT_EQ(0, first[0]);
    EXPECT_EQ(2, first[2]);
    
    EXPECT_EQ(7, rest.size());
    EXPECT_EQ(3, rest[0]);
    EXPECT_EQ(9, rest[6]);
}

TEST(BufptrTest, ChainedSkipOperations) {
    unsigned char data[20];
    for (size_t i = 0; i < 20; ++i) {
        data[i] = static_cast<unsigned char>(i);
    }
    bufptr_t buf(data, 20);
    
    auto result = buf.skip(5).skip(3).skip(2);
    
    EXPECT_EQ(10, result.size());
    EXPECT_EQ(10, *result);  // Should point to data[10]
}

TEST(BufptrTest, CompoundAdditionAndTake) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf(data, 10);
    
    buf += 2;
    auto taken = buf.take(5);
    
    EXPECT_EQ(5, taken.size());
    EXPECT_EQ(2, taken[0]);
    EXPECT_EQ(6, taken[4]);
}

// ============================================================================
// Const Correctness Tests
// ============================================================================

TEST(BufptrTest, ConstBufferPointer) {
    const unsigned char data[5] = {1, 2, 3, 4, 5};
    cbufptr_t buf(data, 5);
    
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(3, buf[2]);
}

TEST(BufptrTest, ConstMethodsOnNonConstBuffer) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    const bufptr_t buf(data, 5);
    
    // These should all work on const buffer
    EXPECT_EQ(5, buf.size());
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(1, buf.front());
    EXPECT_EQ(5, buf.back());
}

// ============================================================================
// Edge Cases and Boundary Tests
// ============================================================================

TEST(BufptrTest, SingleElementBuffer) {
    unsigned char data[1] = {42};
    bufptr_t buf(data, 1);
    
    EXPECT_EQ(1, buf.size());
    EXPECT_EQ(42, *buf);
    EXPECT_EQ(42, buf.front());
    EXPECT_EQ(42, buf.back());
    
    buf += 1;
    EXPECT_TRUE(buf.empty());
}

TEST(BufptrTest, LargeBuffer) {
    const size_t kLargeSize = 10000;
    std::vector<unsigned char> data(kLargeSize);
    for (size_t i = 0; i < kLargeSize; ++i) {
        data[i] = static_cast<unsigned char>(i % 256);
    }
    
    bufptr_t buf(data);
    
    EXPECT_EQ(kLargeSize, buf.size());
    EXPECT_EQ(0, buf[0]);
    EXPECT_EQ(255, buf[255]);
}

TEST(BufptrTest, ModifyThroughBuffer) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    // Modify through buffer
    for (auto& byte : buf) {
        byte *= 2;
    }
    
    // Check original data was modified
    EXPECT_EQ(2, data[0]);
    EXPECT_EQ(4, data[1]);
    EXPECT_EQ(10, data[4]);
}

TEST(BufptrTest, OverlappingBuffers) {
    unsigned char data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bufptr_t buf1(data, 10);
    bufptr_t buf2(data + 5, 5);
    
    EXPECT_EQ(10, buf1.size());
    EXPECT_EQ(5, buf2.size());
    EXPECT_EQ(5, *buf2);
}

// ============================================================================
// Type Alias Tests
// ============================================================================

TEST(BufptrTest, BufptrTypeAlias) {
    unsigned char data[5] = {1, 2, 3, 4, 5};
    bufptr_t buf(data, 5);
    
    // Ensure bufptr_t is generic_bufptr_t<unsigned char>
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(typeid(unsigned char*), typeid(buf.begin()));
}

TEST(BufptrTest, CbufptrTypeAlias) {
    const unsigned char data[5] = {1, 2, 3, 4, 5};
    cbufptr_t buf(data, 5);
    
    // Ensure cbufptr_t is generic_bufptr_t<const unsigned char>
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(typeid(const unsigned char*), typeid(buf.begin()));
}

// ============================================================================
// Main Entry Point
// ============================================================================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
