#pragma once

#include <math.h>
#include <valarray>
#include "utils/macros.hh"

using namespace std;

template <class T>
struct Vec3 {
    valarray<T> v;
    Vec3() : v(0.0, 3) {}
    Vec3( const valarray<T>& vd) {
        v = vd;
    }
    Vec3( double x, double y, double z ) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
    const T &operator[](uint idx) const {
        return v[idx];
    }
    T &operator[](uint idx) {
        return v[idx];
    }
    Vec3 operator+=(const Vec3 &vec) {
        v[0]+=vec[0];
        v[1]+=vec[1];
        v[2]+=vec[2];
        return *this;
    }
    Vec3 operator+(const Vec3 &vec) const {
        return Vec3( v[0]+vec[0], v[1]+vec[1], v[2]+vec[2] );
    }
    Vec3 operator-(const Vec3 &vec) const {
        return Vec3( v[0]-vec[0], v[1]-vec[1], v[2]-vec[2] );
    }
    Vec3 operator*=(double s) {
        v[0] *= s;
        v[1] *= s;
        v[2] *= s;
        return *this;
    }
    Vec3 operator^(const Vec3 &vec) const {
        return Vec3(v[1]*vec[2]-v[2]*vec[1],v[2]*vec[0]-v[0]*vec[2],v[0]*vec[1]-v[1]*vec[0]);
    }
    Vec3 operator-=(const Vec3 &vec) {
        v[0] -= vec[0];
        v[1] -= vec[1];
        v[2] -= vec[2];
        return *this;
    }
    Vec3 operator*(T s) const {
        return Vec3( s*v[0], s*v[1], s*v[2] );
    }
    Vec3 operator/(T s) const {
        return Vec3( v[0]/s, v[1]/s, v[2]/s );
    }
    T operator*(Vec3<T> vec) const {
        return v[0]*vec[0]+v[1]*vec[1]+v[2]*vec[2];
    }
    T len_square() const {
        return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
    }
    T len() const {
        return sqrtf(len_square());
    }
    Vec3 normal() const {
        Vec3 copy = *this;
        copy.normalize();
        return copy;
    }
    bool normalize() {
        T length = len();
        if( length ) {
            v[0] /= length;
            v[1] /= length;
            v[2] /= length;
        }
        return length > 0.0;
    }
};

template <class T> static inline Vec3<T> operator*(double s, const Vec3<T> &vec) {
    return vec*s;
}

typedef Vec3<float>	    Vec3f;
typedef Vec3<double>	Vec3d;
typedef Vec3<int>		Vec3i;