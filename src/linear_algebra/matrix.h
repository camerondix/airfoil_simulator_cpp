#ifndef AIRFOILS_LINEAR_ALGEBRA_MATRIX_H_
#define AIRFOILS_LINEAR_ALGEBRA_MATRIX_H_

#include <vector>

#include "point.h"

namespace linear_algebra
{
    /// @brief a fixed size mxn matrix of doubles
    class Matrix : public std::vector<std::vector<double>>
    {
    private:
        int m, n;

    public:
        /// @brief an mxn matrix filled with zeros
        /// @param m rows
        /// @param n columns
        Matrix(int m, int n) : std::vector<std::vector<double>>(m, std::vector<double>(n)), m(m), n(n){};

        /// @brief a matrix with values extracted from the point
        /// @param point initial matrix values
        Matrix(const geometry::Point &point) : std::vector<std::vector<double>>({{point.x}, {point.y}, {point.z}}), m(3), n(1){};

        /// @brief gets the matrix row count
        /// @return m
        inline int rowCount() const { return m; };

        /// @brief gets the matrix column count
        /// @return n
        inline int columnCount() const { return n; };

        /// @brief creates a point from a 3x1 matrix
        /// @return point extracted from matrix
        geometry::Point toPoint() const;

        /// @brief gets the value indicating if the matrix is square
        /// @return value indicating if the matrix is square
        inline bool isSquare() const { return m == n; };

        /// @brief gets the identity matrix for the size
        /// @return the identity matrix
        static Matrix identity(int size);

        /// @brief factors a matrix solving the system of linear equations
        /// @param a square A matrix
        /// @param b B matrix
        /// @return the solution x to Ax = B
        static Matrix lowerUpperDecomposition(const Matrix &a, const Matrix &b);
    };

    /// @brief computes the entrywise sum of the two matrices
    /// @param lhs first entry
    /// @param rhs second entry
    /// @return sum of the two matricies
    Matrix operator+(const Matrix &lhs, const Matrix &rhs);

    /// @brief scalar matrix multiplication
    /// @param lhs scalar
    /// @param rhs matrix
    /// @return matrix magnified by scalar
    Matrix operator*(double lhs, const Matrix &rhs);

    /// @brief matrix matrix multiplication
    /// @param lhs left matrix
    /// @param rhs right matrix
    /// @return the product of the two matricies
    Matrix operator*(const Matrix &lhs, const Matrix &rhs);
} // namespace linear_algebra

#endif