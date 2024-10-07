#include "geometry_type.h"
#include "kmath.h"

KINLINE line_3d line_3d_create(point_3d start, point_3d end) {
    return (line_3d){start, end};
}

KINLINE f32 line_3d_length_squared(line_3d line) {
    return vec3_length_squared(vec3_sub(line.start, line.end));
}

KINLINE f32 line_3d_length(line_3d line) {
    return vec3_length(vec3_sub(line.start, line.end));
}

KINLINE ray_3d ray_3d_from_points(point_3d from, point_3d to) {
    ray_3d r = {};
    r.origin = from;
    r.direction = vec3_sub(to, from);
    vec3_normalize(&r.direction);
    return r;
}

KINLINE sphere_3d sphere_3d_create(point_3d position, f32 radius) {
    sphere_3d s = {};
    s.position = position;
    s.radius = radius;
}

KINLINE vec3 aabb_3d_min(aabb_3d* aabb) {
    vec3 p1 = vec3_add(aabb->position, aabb->size);
    vec3 p2 = vec3_sub(aabb->position, aabb->size);
    return (vec3){p1.x < p2.x ? p1.x : p2.x,
                  p1.y < p2.y ? p1.y : p2.y,
                  p1.z < p2.z ? p1.z : p2.z};
}

KINLINE vec3 aabb_3d_max(aabb_3d* aabb) {
    vec3 p1 = vec3_add(aabb->position, aabb->size);
    vec3 p2 = vec3_sub(aabb->position, aabb->size);
    return (vec3){p1.x > p2.x ? p1.x : p2.x,
                  p1.y > p2.y ? p1.y : p2.y,
                  p1.z > p2.z ? p1.z : p2.z};
}

KINLINE aabb_3d aabb_3d_create(vec3 min, vec3 max) {
    aabb_3d aabb = {};
    aabb.position = vec3_mul_scalar(vec3_add(min, max), 0.5f);
    aabb.size = vec3_mul_scalar(vec3_sub(max, min), 0.5f);
    return aabb;
}

KINLINE obb_3d obb_3d_create(point_3d position, vec3 size, quat orientation) {
    obb_3d obb = {};
    obb.position = position;
    obb.size = size;
    obb.orientation = orientation;
    return obb;
}

KINLINE plane_3d plane_3d_create(vec3 normal, f32 distance) {
    plane_3d plane = {};
    plane.normal = normal;
    plane.distance = distance;
    return plane;
}

KINLINE f32 plane_3d_equation(point_3d* point, plane_3d* plane) {
    return vec3_dot(*point, plane->normal) - plane->distance;
}