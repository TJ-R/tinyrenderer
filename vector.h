#pragma once
#include <cassert>
#include <cmath>
#include <iostream>

struct vec2f {
        float x;
        float y;
};

struct vec3f {
        float x;
        float y;
        float z;
};

struct vec3i {
        int x;
        int y;
        int z;
};

/*
 * Generic Template
 */
template <int n> struct vec {
        double data[n] = {0};
        double &operator[](const int i) {
                assert(i >= 0 && i < n);
                return data[i];
        }

        double operator[](const int i) const {
                assert(i >= 0 && i < n);
                return data[i];
        }
};

template <int n> std::ostream &operator<<(std::ostream &out, const vec<n> &v) {

        for (int i = 0; i < n; i++)
                out << v[i] << " ";
        return out;
}

template <int n> vec<n> operator+(const vec<n> &lhs, const vec<n> &rhs) {
        vec<n> res;
        for (int i = 0; i < n; i++) {
                res[i] = lhs[i] + rhs[i];
        }

        return res;
}

template <int n> vec<n> operator-(const vec<n> &lhs, const vec<n> &rhs) {
        vec<n> res;
        for (int i = 0; i < n; i++) {
                res[i] = lhs[i] - rhs[i];
        }

        return res;
}

template <int n> vec<n> operator*(const vec<n> &lhs, const double &rhs) {
        vec<n> res = lhs;
        for (int i = 0; i < n; i++) {
                res[i] * rhs;
        }

        return res;
}

template <int n> vec<n> operator*(const double &lhs, const vec<n> &rhs) {
        return rhs * lhs;
}

template <int n> vec<n> operator/(const vec<n> &lhs, const double &rhs) {
        vec<n> res = lhs;
        for (int i = 0; i < n; i++) {
                res[i] /= rhs;
        }

        return res;
}

// Dot product
template <int n> double operator*(const vec<n> &lhs, const vec<n> &rhs) {
        double res = 0;
        for (int i = 0; i < n; i++) {
                res += lhs[i] * rhs[i];
        }

        return res;
}

/*
 * Vec2 template
 */
template <> struct vec<2> {
        double x = 0, y = 0;
        double &operator[](const int i) {
                assert(i >= 0 && i < 2);
                return i ? y : x;
        }
        double operator[](const int i) const {
                assert(i >= 0 && i < 2);
                return i ? y : x;
        }
};

/*
 * Vec3 template
 */
template <> struct vec<3> {
        double x = 0, y = 0, z = 0;
        double &operator[](const int i) {
                assert(i >= 0 && i < 3);
                return i ? (1 == i ? y : z) : x;
        }
        double operator[](const int i) const {
                assert(i >= 0 && i < 3);
                return i ? (1 == i ? y : z) : x;
        }

        vec<3> cross(vec<3> rhs) {
                return {(y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z),
                        (x * rhs.y) - (y * rhs.x)};
        }
};

/*
 * Vec4 template
 */
template <> struct vec<4> {
        double x = 0, y = 0, z = 0, w = 0;
        double &operator[](const int i) {
                assert(i >= 0 && i < 4);
                return i ? (1 == i ? y : (2 == i ? z : w)) : x;
        }
        double operator[](const int i) const {
                assert(i >= 0 && i < 4);
                return i ? (1 == i ? y : (2 == i ? z : w)) : x;
        }

        vec<2> xy() {
                return {x, y};
        };

        vec<3> xyz() {
                return {x, y, z};
        }
};

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;
