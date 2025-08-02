#ifndef __MATH_H__
#define __MATH_H__

typedef struct {
    float x, y;
} Vec2_t;

typedef struct {
    float x, y, z;
} Vec3_t;

float radians(float degrees);

Vec3_t normalize(const Vec3_t a, const Vec3_t b);

Vec3_t cross(const Vec3_t a, const Vec3_t b);

typedef struct {
    float m[4][4];
} Mat4_t;

#endif // !__MATH_H__
