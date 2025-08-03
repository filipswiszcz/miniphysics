#ifndef __MATH_H__
#define __MATH_H__

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

Vec3_t normalize(const Vec3_t a, const Vec3_t b);

Vec3_t cross(const Vec3_t a, const Vec3_t b);

// MATRIX

#define Mat4(v) ((Mat4_t) {.m = { \
    {v, 0, 0, 0}, \
    {0, v, 0, 0}, \
    {0, 0, v, 0}, \
    {0, 0, 0, v} \
}})

typedef struct {
    float m[4][4];
} Mat4_t;

// QUATERNION

typedef Vec4_t Quat_t;

#endif // !__MATH_H_
