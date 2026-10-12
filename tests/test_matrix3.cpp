#include <gtest/gtest.h>
#include <axis/Matrix3.hpp>
#include "test_helpers.hpp"

using axis::Matrix3;
using axis::Vector3;

namespace {
    constexpr float kTol = 1e-4f;

    Matrix3 MakeA() {
        return Matrix3(1, 2, 3,
                       4, 5, 6,
                       7, 8, 9);
    }

    Matrix3 MakeB() {
        return Matrix3(9, 8, 7,
                       6, 5, 4,
                       3, 2, 1);
    }

    Matrix3 MakeC() {
        return Matrix3(2, 1, 3,
                       0, 4, 1,
                       5, 2, 6);
    }
}

TEST(Matrix3, DefaultConstructorIsIdentity) {
    Matrix3 m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m(i, j), i == j ? 1.0f : 0.0f);
        }
    }
}

TEST(Matrix3, IdentityFunctionGivesIdentityMatrix) {
    Matrix3 m = Matrix3::identity();
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m(i, j), i == j ? 1.0f : 0.0f);
        }
    }
}

TEST(Matrix3, NineArgumentConstructorIsRowMajor) {
    Matrix3 m = MakeA();
    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 2.0f);
    EXPECT_FLOAT_EQ(m(0, 2), 3.0f);
    EXPECT_FLOAT_EQ(m(1, 0), 4.0f);
    EXPECT_FLOAT_EQ(m(2, 0), 7.0f);
    EXPECT_FLOAT_EQ(m(2, 2), 9.0f);
}

TEST(Matrix3, OutOfRangeAccessThrows) {
    Matrix3 m;
    EXPECT_THROW(m(3, 0), std::out_of_range);
    EXPECT_THROW(m(0, 3), std::out_of_range);
    EXPECT_NO_THROW(m(2, 2));

    const Matrix3 cm;
    EXPECT_THROW(cm(3, 0), std::out_of_range);
    EXPECT_THROW(cm(0, 3), std::out_of_range);
    EXPECT_NO_THROW(cm(2, 2));
}

TEST(Matrix3, AddingAAndBGivesAllTens) {
    Matrix3 sum = MakeA() + MakeB();
    Matrix3 allTens(10, 10, 10,
                    10, 10, 10,
                    10, 10, 10);
    EXPECT_TRUE(Mat3Near(sum, allTens, kTol));
}

TEST(Matrix3, SubtractingSelfGivesZeroMatrix) {
    Matrix3 a = MakeA();
    Matrix3 zero(0, 0, 0,
                 0, 0, 0,
                 0, 0, 0);
    EXPECT_TRUE(Mat3Near(a - a, zero, kTol));
}

TEST(Matrix3, AddingThenSubtractingReturnsOriginal) {
    Matrix3 a = MakeA();
    Matrix3 b = MakeB();
    EXPECT_TRUE(Mat3Near((a + b) - b, a, kTol));
}

TEST(Matrix3, MultiplyingByIdentityLeavesMatrixUnchanged) {
    Matrix3 a = MakeA();
    Matrix3 identity;
    EXPECT_TRUE(Mat3Near(a * identity, a, kTol));
    EXPECT_TRUE(Mat3Near(identity * a, a, kTol));
}

TEST(Matrix3, MultiplicationKnownProduct) {
    Matrix3 expected(30, 24, 18,
                     84, 69, 54,
                     138, 114, 90);
    EXPECT_TRUE(Mat3Near(MakeA() * MakeB(), expected, kTol));
}

TEST(Matrix3, MultiplicationIsNotCommutative) {
    Matrix3 ab = MakeA() * MakeB();
    Matrix3 ba = MakeB() * MakeA();
    EXPECT_FLOAT_EQ(ab(0, 0), 30.0f);
    EXPECT_FLOAT_EQ(ba(0, 0), 90.0f);
    EXPECT_FALSE(Mat3Near(ab, ba, kTol));
}

TEST(Matrix3, MultiplicationIsAssociative) {
    Matrix3 a = MakeA();
    Matrix3 b = MakeB();
    Matrix3 c = MakeC();
    EXPECT_TRUE(Mat3Near((a * b) * c, a * (b * c), 1e-3f));
}

TEST(Matrix3, IdentityTimesVectorGivesSameVector) {
    Vector3 v(1, 2, 3);
    Vector3 r = Matrix3() * v;
    EXPECT_FLOAT_EQ(r.x, 1.0f);
    EXPECT_FLOAT_EQ(r.y, 2.0f);
    EXPECT_FLOAT_EQ(r.z, 3.0f);
}

TEST(Matrix3, MultiplyingByUnitXGivesFirstColumn) {
    Vector3 r = MakeA() * Vector3(1, 0, 0);
    EXPECT_FLOAT_EQ(r.x, 1.0f);
    EXPECT_FLOAT_EQ(r.y, 4.0f);
    EXPECT_FLOAT_EQ(r.z, 7.0f);
}

TEST(Matrix3, RotationAboutZMapsXToY) {
    Matrix3 rotation(0, -1, 0,
                     1,  0, 0,
                     0,  0, 1);
    Vector3 r = rotation * Vector3(1, 0, 0);
    EXPECT_FLOAT_EQ(r.x, 0.0f);
    EXPECT_FLOAT_EQ(r.y, 1.0f);
    EXPECT_FLOAT_EQ(r.z, 0.0f);
}

TEST(Matrix3, ScaleMatrixScalesEachComponent) {
    Matrix3 scale(2, 0, 0,
                  0, 3, 0,
                  0, 0, 4);
    Vector3 r = scale * Vector3(1, 1, 1);
    EXPECT_FLOAT_EQ(r.x, 2.0f);
    EXPECT_FLOAT_EQ(r.y, 3.0f);
    EXPECT_FLOAT_EQ(r.z, 4.0f);
}

TEST(Matrix3, ProductAppliedToVectorMatchesApplyingEachInOrder) {
    Matrix3 a = MakeA();
    Matrix3 b = MakeB();
    Vector3 v(1, 2, 3);

    Vector3 viaProduct = (a * b) * v;
    Vector3 stepByStep = a * (b * v);

    EXPECT_FLOAT_EQ(viaProduct.x, stepByStep.x);
    EXPECT_FLOAT_EQ(viaProduct.y, stepByStep.y);
    EXPECT_FLOAT_EQ(viaProduct.z, stepByStep.z);
}

TEST(Matrix3, TransposedSwapsRowsAndColumns) {
    Matrix3 a = MakeA();
    Matrix3 expected(1, 4, 7,
                     2, 5, 8,
                     3, 6, 9);
    EXPECT_TRUE(Mat3Near(a.transposed(), expected, kTol));

    EXPECT_TRUE(Mat3Near(a, MakeA(), kTol));
}

TEST(Matrix3, TransposeInPlaceMatchesTransposed) {
    Matrix3 a = MakeA();
    Matrix3 inPlace = MakeA();
    inPlace.transpose();
    EXPECT_TRUE(Mat3Near(inPlace, a.transposed(), kTol));
}

TEST(Matrix3, TransposingTwiceReturnsOriginal) {
    Matrix3 a = MakeA();
    EXPECT_TRUE(Mat3Near(a.transposed().transposed(), a, kTol));
}

TEST(Matrix3, IdentityAndSymmetricMatrixUnchangedByTranspose) {
    Matrix3 identity;
    Matrix3 symmetric(1, 2, 3,
                      2, 4, 5,
                      3, 5, 6);
    EXPECT_TRUE(Mat3Near(identity.transposed(), identity, kTol));
    EXPECT_TRUE(Mat3Near(symmetric.transposed(), symmetric, kTol));
}

TEST(Matrix3, TransposeOfProductIsReversedProductOfTransposes) {
    Matrix3 a = MakeA();
    Matrix3 b = MakeB();
    EXPECT_TRUE(Mat3Near((a * b).transposed(), b.transposed() * a.transposed(), kTol));
}

TEST(Matrix3, DeterminantOfSingularMatrixIsZero) {
    axis::Matrix3 m(1, 2, 3,
                    4, 5, 6,
                    7, 8, 9);
    EXPECT_NEAR(axis::determinant(m), 0.0f, 1e-5f);
}

TEST(Matrix3, DeterminantKnownValue) {
    axis::Matrix3 m(2, 1, 3,
                    0, 4, 1,
                    5, 2, 6);
    EXPECT_NEAR(axis::determinant(m), -11.0f, 1e-4f);
}

TEST(Matrix3, DeterminantOfIdentityIsOne) {
    EXPECT_NEAR(axis::determinant(Matrix3()), 1.0f, kTol);
}

TEST(Matrix3, DeterminantOfDiagonalIsProductOfDiagonal) {
    Matrix3 m(2, 0, 0,
              0, 3, 0,
              0, 0, 4);
    EXPECT_NEAR(axis::determinant(m), 24.0f, kTol);
}

TEST(Matrix3, DeterminantOfTransposeEqualsOriginal) {
    Matrix3 m = MakeC();
    EXPECT_NEAR(axis::determinant(m.transposed()), axis::determinant(m), kTol);
}

TEST(Matrix3, SwappingTwoRowsNegatesDeterminant) {
    Matrix3 swapped(0, 4, 1,
                    2, 1, 3,
                    5, 2, 6);
    EXPECT_NEAR(axis::determinant(swapped), 11.0f, kTol);
}

TEST(Matrix3, DeterminantOfProductWithDiagonalIsProductOfDeterminants) {
    Matrix3 diagonal(2, 0, 0,
                     0, 3, 0,
                     0, 0, 4);
    EXPECT_NEAR(axis::determinant(MakeC() * diagonal), -264.0f, 1e-3f);
}
