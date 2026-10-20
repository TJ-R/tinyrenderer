#pragma once
#include <cassert>
#include <cmath>
#include <iostream>

// row aligned matrix
template <int n> struct sqr_mat {
        double data[n][n];

        double &operator()(const int column, const int row) {
                return data[column][row];
        };

        double operator()(const int column, const int row) const {
                return data[column][row];
        }

        sqr_mat<n> operator+=(const sqr_mat<n> &rhs) {
#pragma omp parallel for // Saying run loop in parallel
                for (int i = 0; i < n; i++) {
                        for (int j; i < n; j++) {
                                data[i][j] += rhs.data[i][j];
                        }
                }

                return *this;
        }

        sqr_mat<n> operator-=(const sqr_mat<n> &rhs) {
#pragma omp parallel for // Saying run loop in parallel
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                                data[i][j] -= rhs.data[i][j];
                        }
                }

                return *this;
        }
};

template <int n>
inline sqr_mat<n> operator+(sqr_mat<n> lhs, const sqr_mat<n> &rhs) {
        lhs += rhs;
        return lhs;
}

template <int n>
inline sqr_mat<n> operator-(sqr_mat<n> lhs, const sqr_mat<n> &rhs) {
        lhs -= rhs;
        return lhs;
}

/*
 * 2x2 Square Matrix */
typedef sqr_mat<2> sqr_mat2x2;
template <> struct sqr_mat<2> {
        double data[2][2];

        double &operator()(const int column, const int row) {
                return data[column][row];
        };

        double operator()(const int column, const int row) const {
                return data[column][row];
        }

        sqr_mat<2> operator+=(const sqr_mat<2> &rhs) {
#pragma omp parallel for // Saying run loop in parallel
                for (int i = 0; i < 2; i++) {
                        for (int j; i < 2; j++) {
                                data[i][j] += rhs.data[i][j];
                        }
                }

                return *this;
        }

        sqr_mat<2> operator-=(const sqr_mat<2> &rhs) {
#pragma omp parallel for // Saying run loop in parallel
                for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                                data[i][j] -= rhs.data[i][j];
                        }
                }

                return *this;
        }

        sqr_mat<2> transpose() {
                std::swap(data[0][1], data[1][0]);
                return *this;
        }
};

/*
 * 3x3 Square Matrix
 */
typedef sqr_mat<3> sqr_mat3x3;
template <> struct sqr_mat<3> {};

/*
 * 4x4 Square Matrix
 */
typedef sqr_mat<4> sqr_mat4x4;
template <> struct sqr_mat<4> {};
