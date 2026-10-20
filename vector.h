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

        vec<n> &operator+=(const vec<n> &rhs) {
                for (int i = 0; i < n; i++) {
                        data[i] += rhs.data[i];
                }

                return *this;
        }

        vec<n> &operator-=(const vec<n> &rhs) {
                for (int i = 0; i < n; i++) {
                        data[i] -= rhs.data[i];
                }

                return *this;
        }

        double dot(const vec<n> &rhs) {
                double sum = 0;
                for (int i = 0; i < n; i++) {
                        sum += (data[i] * rhs.data[i]);
                }

                return sum;
        }
};

template <int n> std::ostream &operator<<(std::ostream &out, const vec<n> &v) {
        for (int i = 0; i < n; i++)
                out << v[i] << " ";
        return out;
}

template <int n> inline vec<n> operator+(vec<n> lhs, const vec<n> &rhs) {
        lhs += rhs;
        return lhs;
}

template <int n> inline vec<n> operator-(vec<n> lhs, const vec<n> &rhs) {
        lhs -= rhs;
        return lhs;
}

/*
 * Vec2 template
 */
typedef vec<2> vec2;
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

        vec<2> &operator+=(const vec<2> &rhs) {
                x += rhs.x;
                y += rhs.y;

                return *this;
        }

        vec<2> &operator-=(const vec<2> &rhs) {
                x -= rhs.x;
                y -= rhs.y;

                return *this;
        }

        double dot(const vec<2> &rhs) {
                return (x * rhs.x) + (y * rhs.y);
        }

        // I think this is right
        double cross(const vec<2> &rhs) {
                return (this->x * rhs.y) - (this->y * rhs.x);
        }
};

template <> inline vec<2> operator+(vec<2> lhs, const vec<2> &rhs) {
        lhs += rhs;
        return lhs;
}

template <> inline vec<2> operator-(vec<2> lhs, const vec<2> &rhs) {
        lhs -= rhs;
        return lhs;
}

/*
 * Vec3 template
 */
typedef vec<3> vec3;
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

        // Using determinant of 3x3 matrix?
        // vec<3> cross(const vec<3> &rhs) {
        //         double xcomp = (this->y * rhs.z - this->z * rhs.y);
        //         double ycomp = (this->z * rhs.x - this->x * rhs.z);
        //         double zcomp = (this->x * rhs.y - this->y * rhs.x);
        //
        //         // Needs fixd
        //         return xcomp + ycomp + zcomp;
        // }
};

/*
 * Vec4 template
 */
typedef vec<4> vec4;
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
};
