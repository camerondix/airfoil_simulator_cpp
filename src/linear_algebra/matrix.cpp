#include "matrix.h"

#include "point.h"

using linear_algebra::Matrix;

using geometry::Point;

Point Matrix::toPoint() const
{
    if (rowCount() != 3)
        throw std::invalid_argument("The matrix must have exactly three rows");
    if (columnCount() != 1)
        throw std::invalid_argument("The matrix must have exactly one column");
    return Point{(*this)[0][0], (*this)[1][0], (*this)[2][0]};
}

Matrix Matrix::identity(int size)
{
    Matrix m(size, size);
    for (int i = 0; i < size; ++i)
        m.at(i).at(i) = 1;
    return m;
}

Matrix Matrix::lowerUpperDecomposition(const Matrix &a, const Matrix &b)
{
    // TODO: throw an exception if leading principle minors are zero
    if (!a.isSquare())
        throw std::invalid_argument("The a matrix must be square");
    if (b.columnCount() != 1)
        throw std::invalid_argument("The b matrix must have exactly one column");
    if (a.rowCount() != b.rowCount())
        throw std::invalid_argument("The a and b matricies must have a matching row count");

    int order = a.rowCount();
    Matrix lu(order, order);
    double sum = 0.0;
    // decomposition
    for (int i = 0; i < order; ++i)
    {
        for (int j = i; j < order; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(i).at(k) * lu.at(k).at(j);
            lu.at(i).at(j) = a.at(i).at(j) - sum;
        }
        for (int j = i + 1; j < order; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(j).at(k) * lu.at(k).at(i);
            lu.at(j).at(i) = (1 / lu.at(i).at(i)) * (a.at(j).at(i) - sum);
        }
    }
    // solve Ly = b
    Matrix y(order, 1);
    for (int i = 0; i < order; ++i)
    {
        sum = 0;
        for (int k = 0; k < i; k++)
            sum += lu.at(i).at(k) * y.at(k).at(0);
        y.at(i).at(0) = b.at(i).at(0) - sum;
    }
    // solve Ux = y
    Matrix x(order, 1);
    for (int i = order - 1; i >= 0; i--)
    {
        sum = 0;
        for (int k = i + 1; k < order; k++)
            sum += lu.at(i).at(k) * x.at(k).at(0);
        x.at(i).at(0) = (1 / lu.at(i).at(i)) * (y.at(i).at(0) - sum);
    }
    return x;
};

Matrix linear_algebra::operator+(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.rowCount() != rhs.rowCount())
        throw std::invalid_argument("The matricies must have a matching row count");
    if (lhs.columnCount() != rhs.columnCount())
        throw std::invalid_argument("The matricies must have a matching column count");

    int m = lhs.rowCount();
    int n = lhs.columnCount();
    Matrix matrix(m, n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; j++)
            matrix.at(i).at(j) = lhs.at(i).at(j) + rhs.at(i).at(j);
    return matrix;
}

Matrix linear_algebra::operator*(double lhs, const Matrix &rhs)
{
    int m = rhs.rowCount();
    int n = rhs.columnCount();
    Matrix matrix(m, n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; j++)
            matrix.at(i).at(j) = lhs * rhs.at(i).at(j);
    return matrix;
}

Matrix linear_algebra::operator*(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.columnCount() != rhs.rowCount())
        throw std::invalid_argument("The left matrix column count must match the right matrix row count");

    int m = lhs.rowCount();
    int n = lhs.columnCount();
    int p = rhs.columnCount();
    Matrix matrix(m, p);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < n; k++)
                matrix.at(i).at(j) += lhs.at(i).at(k) * rhs.at(k).at(j);
    return matrix;
}