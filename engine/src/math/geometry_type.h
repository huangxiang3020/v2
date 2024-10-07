#pragma once

#include "defines.h"
#include "math/math_types.h"

typedef vec3 point_3d;

typedef struct line_3d {
    point_3d start;
    point_3d end;
} line_3d;

typedef struct ray_3d {
    point_3d origin;
    vec3 direction;
} ray_3d;

typedef struct sphere_3d {
    point_3d position;
    f32 radius;
} sphere_3d;

typedef struct aabb_3d {
    point_3d position;
    vec3 size;
} aabb_3d;

typedef struct obb_3d {
    point_3d position;
    vec3 size;
    quat orientation;
} obb_3d;

typedef struct plane_3d {
    vec3 normal;
    f32 distance;
} plane_3d;

typedef union triangle_3d {
    struct {
        plane_3d a;
        point_3d b;
        point_3d c;
    };
    point_3d points[3];
    f32 values[9];
} triangle_3d;