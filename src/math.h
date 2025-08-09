#ifndef __MATH_H__
#define __MATH_H__

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cmath>

// FLOAT

/*float sin(float v);

float cos(float v);

float tan(float v);

float q_tan(float v);

float q_rsqrt(float v);*/

// VECTOR

typedef struct Vec2 {
    float x, y;

    Vec2 operator+(const Vec2 &o) const {
        return {x + o.x, y + o.y};
    }
    Vec2 &operator+=(const Vec2 &o) {
        return (x += o.x, y += o.y, *this);
    }
    Vec2 operator-(const Vec2 &o) const {
        return {x - o.x, y - o.y};
    }
    Vec2 &operator-=(const Vec2 &o) {
        return (x -= o.x, y -= o.y, *this);
    }
    Vec2 operator*(const float s) const {
        return {x * s, y * s};
    } // scalar should be type-free
    Vec2 &operator*=(const float s) {
        return (x *= s, y *= s, *this);
    }

} Vec2_t;

typedef struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3 &o) const {
        return {x + o.x, y + o.y, z + o.z};
    }
    Vec3 &operator+=(const Vec3 &o) {
        return (x += o.x, y += o.y, z += o.z, *this);
    }
    Vec3 operator-(const Vec3 &o) const {
        return {x - o.x, y - o.y, z - o.z};
    }
    Vec3 &operator-=(const Vec3 &o) {
        return (x -= o.x, y -= o.y, z -= o.z, *this);
    }
    Vec3 operator*(const float s) const {
        return {x * s, y * s, z * s};
    }
    Vec3 &operator*=(const float s) {
        return (x *= s, y *= s, z *= s, *this);
    }

} Vec3_t;

typedef struct Vec4 {
    float x, y, z, w;

    Vec4 operator+(const Vec4 &o) const {
        return {x + o.x, y + o.y, z + o.z, w + o.w};
    }
    Vec4 &operator+=(const Vec4 &o) {
        return (x += o.x, y += o.y, z += o.z, w += o.w, *this);
    }
    Vec4 operator-(const Vec4 &o) const {
        return {x - o.x, y - o.y, z - o.z, w - o.w};
    }
    Vec4 &operator-=(const Vec4 &o) {
        return (x -= o.x, y -= o.y, z -= o.z, w -= o.w, *this);
    }
    Vec4 operator*(const float s) const {
        return {x * s, y * s, z * s, w * s};
    }
    Vec4 &operator*=(const float s) {
        return (x *= s, y *= s, z *= s, w *= s, *this);
    }

} Vec4_t;

float radians(float degrees);

Vec3_t normalize(const Vec3_t v);

Vec3_t cross(const Vec3_t a, const Vec3_t b);

// MATRIX

/*#define Mat4(v) ((Mat4_t) {{ \
    {v, 0, 0, 0}, \
    {0, v, 0, 0}, \
    {0, 0, v, 0}, \
    {0, 0, 0, v} \
}})*/

typedef struct Mat4 {
    float m[4][4];

    explicit Mat4(float v) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = (i == j) ? v : 0;
            }
        }
    }
    
} Mat4_t;

static void _read_mat4(Mat4_t m) {
    for (int i = 0; i < 4; i++) { // fun fact: cpu registers are of ten 32 or 64-bit wide and the loop control variables are almost always stored in CPU registers
        std::cout << "[";
        for (int j = 0; j < 4; j++) {
            // std::cout << std::fixed << ((width) ? std::setw(width) : std::setw(1)) << std::setprecision(6) << m.m[i][j]; it doesn't fucking work :(
            std::cout << std::fixed << std::setprecision(6) << m.m[i][j];
            if (j < 3) std::cout << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

Mat4_t orthographic(float l, float r, float b, float t, float znear, float zfar);

Mat4_t perspective(float fovy, float aspect, float znear, float zfar);

Mat4_t translate(Mat4_t m, Vec3_t v);

Mat4_t rotate(Mat4_t m, float angle, Vec3_t v);

Mat4_t look_at(Vec3_t pos, Vec3_t target, Vec3_t up);

// QUATERNION

typedef Vec4_t Quat_t;

Mat4_t rotate_quat(Mat4_t m, Quat_t q);

#endif // !__MATH_H_
