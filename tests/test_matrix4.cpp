#include <gtest/gtest.h>
#include <axis/Matrix4.hpp>
#include "test_helpers.hpp"

using axis::Matrix4;
using axis::Vector4;

namespace {
    constexpr float kTol = 1e-4f;

    Matrix4 MakeM16() {
        return Matrix4(1,  2,  3,  4,
                       5,  6,  7,  8,
                       9,  10, 11, 12,
                       13, 14, 15, 16);
    }

    Matrix4 MakeM16Reversed() {
        return Matrix4(16, 15, 14, 13,
                       12, 11, 10, 9,
                       8,  7,  6,  5,
                       4,  3,  2,  1);
    }

    Matrix4 MakeTranslation(float x, float y, float z) {
        return Matrix4(1, 0, 0, x,
                       0, 1, 0, y,
                       0, 0, 1, z,
                       0, 0, 0, 1);
    }

    Matrix4 MakeRotationZ90() {
        return Matrix4(0, -1, 0, 0,
                       1,  0, 0, 0,
                       0,  0, 1, 0,
                       0,  0, 0, 1);
    }

    Matrix4 MakeDet58() {
        return Matrix4(1, 2, 0, 1,
                       0, 1, 3, 2,
                       4, 0, 1, 1,
                       2, 1, 0, 3);
    }
}

TEST(Matrix4, DefaultConstructorIsIdentity) {
    Matrix4 m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(m(i, j), i == j ? 1.0f : 0.0f);
        }
    }
}

TEST(Matrix4, IdentityFunctionGivesIdentityMatrix) {
    Matrix4 m = Matrix4::identity();
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            EXPECT_FLOAT_EQ(m(i, j), i == j ? 1.0f : 0.0f);
        }
    }
}

TEST(Matrix4, SixteenArgumentConstructorIsRowMajor) {
    Matrix4 m = MakeM16();
    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 3), 4.0f);
    EXPECT_FLOAT_EQ(m(1, 2), 7.0f);
    EXPECT_FLOAT_EQ(m(3, 0), 13.0f);
    EXPECT_FLOAT_EQ(m(3, 3), 16.0f);
}

TEST(Matrix4, OutOfRangeAccessThrows) {
    Matrix4 m;
    EXPECT_THROW(m(4, 0), std::out_of_range);
    EXPECT_THROW(m(0, 4), std::out_of_range);
    EXPECT_NO_THROW(m(3, 3));

    const Matrix4 cm;
    EXPECT_THROW(cm(4, 0), std::out_of_range);
    EXPECT_THROW(cm(0, 4), std::out_of_range);
    EXPECT_NO_THROW(cm(3, 3));
}

TEST(Matrix4, ConstAccessToLastRowAndColumnWorks) {
    const Matrix4 m(1,  2,  3,  4,
                    5,  6,  7,  8,
                    9,  10, 11, 12,
                    13, 14, 15, 16);
    EXPECT_NO_THROW(m(3, 3));
    EXPECT_FLOAT_EQ(m(0, 3), 4.0f);
    EXPECT_FLOAT_EQ(m(3, 0), 13.0f);
    EXPECT_FLOAT_EQ(m(3, 3), 16.0f);
}

TEST(Matrix4, AddingM16AndReversedGivesAllSeventeens) {
    Matrix4 sum = MakeM16() + MakeM16Reversed();
    Matrix4 allSeventeen(17, 17, 17, 17,
                         17, 17, 17, 17,
                         17, 17, 17, 17,
                         17, 17, 17, 17);
    EXPECT_TRUE(Mat4Near(sum, allSeventeen, kTol));
}

TEST(Matrix4, SubtractingSelfGivesZeroMatrix) {
    Matrix4 m = MakeM16();
    Matrix4 zero(0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0,
                 0, 0, 0, 0);
    EXPECT_TRUE(Mat4Near(m - m, zero, kTol));
}

TEST(Matrix4, MultiplyingByIdentityLeavesMatrixUnchanged) {
    Matrix4 m = MakeM16();
    Matrix4 identity;
    EXPECT_TRUE(Mat4Near(m * identity, m, kTol));
    EXPECT_TRUE(Mat4Near(identity * m, m, kTol));
}

TEST(Matrix4, TranslationsCompose) {
    Matrix4 combined = MakeTranslation(1, 2, 3) * MakeTranslation(4, 5, 6);
    EXPECT_TRUE(Mat4Near(combined, MakeTranslation(5, 7, 9), kTol));
}

TEST(Matrix4, OrderOfTransformsMatters) {
    Matrix4 translate = MakeTranslation(1, 0, 0);
    Matrix4 rotate = MakeRotationZ90();
    Vector4 origin(0, 0, 0, 1);

    Vector4 a = (translate * rotate) * origin;
    Vector4 b = (rotate * translate) * origin;

    EXPECT_FLOAT_EQ(a.x, 1.0f);
    EXPECT_FLOAT_EQ(a.y, 0.0f);
    EXPECT_FLOAT_EQ(a.z, 0.0f);
    EXPECT_FLOAT_EQ(a.w, 1.0f);

    EXPECT_FLOAT_EQ(b.x, 0.0f);
    EXPECT_FLOAT_EQ(b.y, 1.0f);
    EXPECT_FLOAT_EQ(b.z, 0.0f);
    EXPECT_FLOAT_EQ(b.w, 1.0f);
}

TEST(Matrix4, IdentityTimesVectorGivesSameVector) {
    Vector4 v(1, 2, 3, 4);
    Vector4 r = Matrix4() * v;
    EXPECT_FLOAT_EQ(r.x, 1.0f);
    EXPECT_FLOAT_EQ(r.y, 2.0f);
    EXPECT_FLOAT_EQ(r.z, 3.0f);
    EXPECT_FLOAT_EQ(r.w, 4.0f);
}

TEST(Matrix4, TranslationMovesAPoint) {
    Vector4 r = MakeTranslation(1, 2, 3) * Vector4(1, 1, 1, 1);
    EXPECT_FLOAT_EQ(r.x, 2.0f);
    EXPECT_FLOAT_EQ(r.y, 3.0f);
    EXPECT_FLOAT_EQ(r.z, 4.0f);
    EXPECT_FLOAT_EQ(r.w, 1.0f);
}

TEST(Matrix4, TranslationDoesNotMoveADirection) {
    Vector4 r = MakeTranslation(1, 2, 3) * Vector4(1, 1, 1, 0);
    EXPECT_FLOAT_EQ(r.x, 1.0f);
    EXPECT_FLOAT_EQ(r.y, 1.0f);
    EXPECT_FLOAT_EQ(r.z, 1.0f);
    EXPECT_FLOAT_EQ(r.w, 0.0f);
}

TEST(Matrix4, BasisVectorsPickOutFirstAndLastColumns) {
    Vector4 first = MakeM16() * Vector4(1, 0, 0, 0);
    EXPECT_FLOAT_EQ(first.x, 1.0f);
    EXPECT_FLOAT_EQ(first.y, 5.0f);
    EXPECT_FLOAT_EQ(first.z, 9.0f);
    EXPECT_FLOAT_EQ(first.w, 13.0f);

    Vector4 last = MakeM16() * Vector4(0, 0, 0, 1);
    EXPECT_FLOAT_EQ(last.x, 4.0f);
    EXPECT_FLOAT_EQ(last.y, 8.0f);
    EXPECT_FLOAT_EQ(last.z, 12.0f);
    EXPECT_FLOAT_EQ(last.w, 16.0f);
}

TEST(Matrix4, RotationAboutZMapsXToY) {
    Vector4 r = MakeRotationZ90() * Vector4(1, 0, 0, 1);
    EXPECT_FLOAT_EQ(r.x, 0.0f);
    EXPECT_FLOAT_EQ(r.y, 1.0f);
    EXPECT_FLOAT_EQ(r.z, 0.0f);
    EXPECT_FLOAT_EQ(r.w, 1.0f);
}

TEST(Matrix4, TransposedSwapsRowsAndColumns) {
    Matrix4 m = MakeM16();
    Matrix4 expected(1, 5, 9,  13,
                     2, 6, 10, 14,
                     3, 7, 11, 15,
                     4, 8, 12, 16);

    Matrix4 t = m.transposed();
    EXPECT_TRUE(Mat4Near(t, expected, kTol));
    EXPECT_FLOAT_EQ(t(0, 3), 13.0f);
    EXPECT_FLOAT_EQ(t(3, 0), 4.0f);

    // The original must be unchanged
    EXPECT_TRUE(Mat4Near(m, MakeM16(), kTol));
}

TEST(Matrix4, TransposeInPlaceMatchesTransposed) {
    Matrix4 m = MakeM16();
    Matrix4 inPlace = MakeM16();
    inPlace.transpose();
    EXPECT_TRUE(Mat4Near(inPlace, m.transposed(), kTol));
}

TEST(Matrix4, TransposingTwiceReturnsOriginal) {
    Matrix4 m = MakeM16();
    EXPECT_TRUE(Mat4Near(m.transposed().transposed(), m, kTol));
}

TEST(Matrix4, TransposeOfProductIsReversedProductOfTransposes) {
    Matrix4 a = MakeM16();
    Matrix4 b = MakeM16Reversed();
    EXPECT_TRUE(Mat4Near((a * b).transposed(), b.transposed() * a.transposed(), kTol));
}

TEST(Matrix4, DeterminantOfIdentityIsOne) {
    EXPECT_NEAR(axis::determinant(Matrix4()), 1.0f, 1e-5f);
}

TEST(Matrix4, DeterminantOfDiagonalIsProductOfDiagonal) {
    Matrix4 m(2, 0, 0, 0,
              0, 3, 0, 0,
              0, 0, 4, 0,
              0, 0, 0, 5);
    EXPECT_NEAR(axis::determinant(m), 120.0f, 1e-3f);
}

TEST(Matrix4, DeterminantOfSingularMatrixIsZero) {
    Matrix4 m(1, 2, 3, 4,
              1, 2, 3, 4,
              5, 6, 7, 8,
              2, 0, 1, 3);
    EXPECT_NEAR(axis::determinant(m), 0.0f, 1e-4f);
}

TEST(Matrix4, DeterminantKnownValue) {
    Matrix4 m(1, 2, 0, 1,
              0, 1, 3, 2,
              4, 0, 1, 1,
              2, 1, 0, 3);
    EXPECT_NEAR(axis::determinant(m), 58.0f, 1e-3f);
}

TEST(Matrix4, DeterminantOfTransposeEqualsOriginal) {
    Matrix4 m = MakeDet58();
    EXPECT_NEAR(axis::determinant(m.transposed()), axis::determinant(m), 1e-3f);
}

TEST(Matrix4, SwappingTwoRowsNegatesDeterminant) {
    Matrix4 swapped(0, 1, 3, 2,
                    1, 2, 0, 1,
                    4, 0, 1, 1,
                    2, 1, 0, 3);
    EXPECT_NEAR(axis::determinant(swapped), -58.0f, 1e-3f);
}

TEST(Matrix4, DeterminantOfTranslationAndRotationIsOne) {
    EXPECT_NEAR(axis::determinant(MakeTranslation(1, 2, 3)), 1.0f, kTol);
    EXPECT_NEAR(axis::determinant(MakeRotationZ90()), 1.0f, kTol);
}

TEST(Matrix4, DeterminantMatchesMatrix3WhenEmbedded) {
    Matrix4 embedded(2, 1, 3, 0,
                     0, 4, 1, 0,
                     5, 2, 6, 0,
                     0, 0, 0, 1);
    axis::Matrix3 inner(2, 1, 3,
                        0, 4, 1,
                        5, 2, 6);
    EXPECT_NEAR(axis::determinant(embedded), axis::determinant(inner), kTol);
    EXPECT_NEAR(axis::determinant(embedded), -11.0f, kTol);
}

TEST(Matrix4, DeterminantOfProductWithDiagonalIsProductOfDeterminants) {
    Matrix4 diagonal(2, 0, 0, 0,
                     0, 3, 0, 0,
                     0, 0, 4, 0,
                     0, 0, 0, 5);
    EXPECT_NEAR(axis::determinant(MakeDet58() * diagonal), 6960.0f, 0.05f);
}
