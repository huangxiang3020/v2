#pragma once
#include "renderer/renderer_types.inl"

typedef struct geometry_system_config {
    u32 max_geometry_count;
} geometry_system_config;

typedef struct geometry_config {
    u32 vertex_count;
    vertex_3d* vertices;
    u32 index_count;
    u32* indices;
    char name[GEOMETRY_NAME_MAX_LENGTH];
    char material_name[MATERIAL_NAME_MAX_LENGTH];
} geometry_config;

#define DEFAULT_GEOMETRY_NAME "default"

b8 geometry_system_initialize(u64* memory_requirement, void* state, geometry_system_config config);
void geometry_system_shutdown(void* state);

geometry* geometry_system_acquire_by_id(u32 id);

geometry* geometry_system_acquire_from_config(geometry_config config, b8 auto_release);

void geometry_system_release(geometry* geometry);

geometry* geometry_system_get_default();

geometry_config geometry_system_generate_plane_config(f32 width, f32 height, u32 x_segment_count, u32 y_segment_count, f32 tile_x, f32 tile_y, const char* name, const char* material_name);
