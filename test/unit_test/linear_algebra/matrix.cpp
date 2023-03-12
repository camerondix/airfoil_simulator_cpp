#include "matrix.h"

#include <gtest/gtest.h>

#include "point.h"

using geometry::Point;
using linear_algebra::Matrix;

namespace
{
    TEST(Matrix, MatrixDefault)
    {
        Matrix m(2, 2);
        ASSERT_FLOAT_EQ(m[0][0], 0.0);
        ASSERT_FLOAT_EQ(m[0][1], 0.0);
        ASSERT_FLOAT_EQ(m[1][0], 0.0);
        ASSERT_FLOAT_EQ(m[1][1], 0.0);
    }

    TEST(Matrix, MatrixPoint)
    {
        Point p{1.25, 2.5, 3.75};
        Matrix m{p};
        ASSERT_FLOAT_EQ(m[0][0], 1.25);
        ASSERT_FLOAT_EQ(m[1][0], 2.5);
        ASSERT_FLOAT_EQ(m[2][0], 3.75);
    }

    TEST(Matrix, identity2x2)
    {
        Matrix m = Matrix::identity(2);
        ASSERT_FLOAT_EQ(m[0][0], 1.0);
        ASSERT_FLOAT_EQ(m[0][1], 0.0);
        ASSERT_FLOAT_EQ(m[1][0], 0.0);
        ASSERT_FLOAT_EQ(m[1][1], 1.0);
    }

    TEST(Matrix, identity3x3)
    {
        Matrix m = Matrix::identity(3);
        ASSERT_FLOAT_EQ(m[0][0], 1.0);
        ASSERT_FLOAT_EQ(m[0][1], 0.0);
        ASSERT_FLOAT_EQ(m[0][2], 0.0);
        ASSERT_FLOAT_EQ(m[1][0], 0.0);
        ASSERT_FLOAT_EQ(m[1][1], 1.0);
        ASSERT_FLOAT_EQ(m[1][2], 0.0);
        ASSERT_FLOAT_EQ(m[2][0], 0.0);
        ASSERT_FLOAT_EQ(m[2][1], 0.0);
        ASSERT_FLOAT_EQ(m[2][2], 1.0);
    }

    TEST(Matrix, toPoint)
    {
        Matrix m(3, 1);
        m[0][0] = 1.25;
        m[1][0] = 2.5;
        m[2][0] = 3.75;
        Point p = m.toPoint();
        ASSERT_FLOAT_EQ(p.x, 1.25);
        ASSERT_FLOAT_EQ(p.y, 2.5);
        ASSERT_FLOAT_EQ(p.z, 3.75);
    }

    TEST(Matrix, toPointInvalidArguments)
    {
        ASSERT_THROW(Matrix(4, 1).toPoint(), std::invalid_argument);
        ASSERT_THROW(Matrix(3, 2).toPoint(), std::invalid_argument);
    }

    TEST(Matrix, addition)
    {
        Matrix m1(2, 2);
        m1[0][0] = 1.25;
        m1[0][1] = 2.5;
        m1[1][0] = 3.75;
        m1[1][1] = 4.0;
        Matrix m2(2, 2);
        m2[0][0] = 4.0;
        m2[0][1] = 3.75;
        m2[1][0] = 2.5;
        m2[1][1] = 1.25;
        Matrix m = m1 + m2;
        ASSERT_FLOAT_EQ(m[0][0], 5.25);
        ASSERT_FLOAT_EQ(m[0][1], 6.25);
        ASSERT_FLOAT_EQ(m[1][0], 6.25);
        ASSERT_FLOAT_EQ(m[1][1], 5.25);
    }

    TEST(Matrix, additionInvalidArguments)
    {
        ASSERT_THROW(Matrix(4, 3) + Matrix(3, 3), std::invalid_argument);
        ASSERT_THROW(Matrix(3, 4) + Matrix(3, 3), std::invalid_argument);
    }

    TEST(Matrix, multiplicationScalar)
    {
        Matrix m(2, 2);
        m[0][0] = 1.25;
        m[0][1] = 2.5;
        m[1][0] = 3.75;
        m[1][1] = 4.0;
        m = 2.5 * m;
        ASSERT_FLOAT_EQ(m[0][0], 3.125);
        ASSERT_FLOAT_EQ(m[0][1], 6.25);
        ASSERT_FLOAT_EQ(m[1][0], 9.375);
        ASSERT_FLOAT_EQ(m[1][1], 10.0);
    }

    TEST(Matrix, multiplication2x2x2)
    {
        Matrix m1(2, 2);
        m1[0][0] = 1.25;
        m1[0][1] = 2.5;
        m1[1][0] = 3.75;
        m1[1][1] = 4.0;
        Matrix m2(2, 2);
        m2[0][0] = 4.0;
        m2[0][1] = 3.75;
        m2[1][0] = 2.5;
        m2[1][1] = 1.25;
        Matrix m = m1 * m2;
        ASSERT_FLOAT_EQ(m[0][0], 11.25);
        ASSERT_FLOAT_EQ(m[0][1], 7.8125);
        ASSERT_FLOAT_EQ(m[1][0], 25.0);
        ASSERT_FLOAT_EQ(m[1][1], 19.0625);
    }

    TEST(Matrix, multiplicationInvalidArguments)
    {
        ASSERT_THROW(Matrix(3, 4) * Matrix(3, 4), std::invalid_argument);
    }

    TEST(Matrix, lowerUpperDecomposition)
    {
        Matrix a(3, 3);
        a[0][0] = 1;
        a[0][1] = -2;
        a[0][2] = 3;
        a[1][0] = -1;
        a[1][1] = 3;
        a[1][2] = -1;
        a[2][0] = 2;
        a[2][1] = -5;
        a[2][2] = 5;
        Matrix b(3, 1);
        b[0][0] = 9;
        b[1][0] = -6;
        b[2][0] = 17;
        Matrix answer = Matrix::lowerUpperDecomposition(a, b);
        ASSERT_FLOAT_EQ(answer[0][0], 1);
        ASSERT_FLOAT_EQ(answer[1][0], -1);
        ASSERT_FLOAT_EQ(answer[2][0], 2);
    }

    TEST(Matrix, lowerUpperDecompositionInvalidArguments)
    {
        ASSERT_THROW(Matrix::lowerUpperDecomposition(Matrix(3, 4), Matrix(3, 1)), std::invalid_argument);
        ASSERT_THROW(Matrix::lowerUpperDecomposition(Matrix(3, 3), Matrix(3, 2)), std::invalid_argument);
        ASSERT_THROW(Matrix::lowerUpperDecomposition(Matrix(3, 3), Matrix(4, 1)), std::invalid_argument);
    }
} // namespace