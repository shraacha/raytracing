#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    double e[3];

public:
    vec3 () : e{0,0,0} {}
    vec3 (double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3 & operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 & operator*=(const double c) {
        e[0] *= c;
        e[1] *= c;
        e[2] *= c;
        return *this;
    }

    vec3 & operator/=(const double c) {
        return *this *= 1/c;
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    double length() const {
        return sqrt(length_squared());
    }
};

// type aliases for vec3 since it will be used for both 3D points and Colour
/*
** - Using the vec3 class for colour as well as points is usually frowned upon: it is thought to be better to separate the functionality and
** prevent say "adding a colour and location"
**   - for the sake of simplicity, we combine them
*/

using point3 = vec3;     // 3D point
using colour = vec3;     // Colour

// vec3 utility functions

inline std::ostream& operator<< (std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3 &v, const double c) {
    return vec3(v.e[0] * c, v.e[1] * c, v.e[2] * c);
}

inline vec3 operator*(const double c, const vec3 &v) {
    return v * c;
}

inline vec3 operator/(vec3 v, double c) {
    return v * (1/c);
}


inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                -(u.e[0] * v.e[2] - u.e[2] * v.e[0]),
                u.e[1] * v.e[2] - u.e[2] * v.e[1]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif
