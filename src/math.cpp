#include "math.h"

// FLOAT

float q_rsqrt(float v) {
    long i;
    float x2, y;

    x2 = v * 0.5f;
    y = v;
    i = *(long*) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y = y * (1.5f - (x2 * y * y));
    
    return y;
}

// VECTOR

float radians(float degrees) {
    return degrees * 0.01745329251994329576923690768489;
}

Vec3_t normalize(const Vec3_t v) {
    float l = v.x * v.x + v.y * v.y + v.z * v.z;
    float rl = q_rsqrt(l);
    return {v.x * rl, v.y * rl, v.z * rl};
}

Vec3_t cross(const Vec3_t a, const Vec3_t b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float dot(const Vec3_t a, const Vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// MATRIX

void __read_mat4(Mat4_t m) {}
