#include "math.h"

// FLOAT

float q_tan(float v) { // blows up near +-PI/2 (90 or -90 degrees)
    float pisqby4 = 2.4674011002723397f;
    float om8bypisq = 0.1894305308612978f;
    float vsq = v * v;
    return v * (pisqby4 - om8bypisq * vsq) / (pisqby4 - vsq);
}

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

void __read_mat4(Mat4_t m) {
    for (int i = 0; i < 4; i++) { // fun fact: cpu registers are often 32 or 64-bit wide and the loop control variables are almost always stored in CPU registers
        std::cout << "[";
        for (int j = 0; j < 4; j++) {
            std::cout << std::fixed << std::setw(7) << std::setprecision(2) << m.m[i][j];
            if (j < 3) std::cout << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

Mat4_t orthographic(float l, float r, float b, float t, float znear, float zfar) {
    Mat4_t res = Mat4(0);
    res.m[0][0] = 2.0f / (r - l);
    res.m[1][1] = 2.0f / (t - b);
    res.m[2][2] = -2.0f / (zfar / znear);
    res.m[3][0] = -(r + l) / (r - l);
    res.m[3][1] = -(t + b) / (t - b);
    res.m[3][2] = -(zfar + znear) / (zfar - znear);
    res.m[3][3] = 1.0f;
    return res;
}

Mat4_t perspective(float fovy, float aspect, float znear, float zfar) {
    float rad = fovy;
    float tan_half_fovy = q_tan(rad / 2);

    Mat4_t res = Mat4(0);
    res.m[0][0] = 1.0f / (aspect * tan_half_fovy);
    res.m[1][1] = 1.0f / (tan_half_fovy);
    res.m[2][2] = -(zfar + znear) / (zfar - znear);
    res.m[2][3] = -1.0f;
    res.m[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
    res.m[3][3] = 0.0f;

    return res;
}
