#include "renderer_frontend.h"

#include "core/event.h"
#include "core/kmemory.h"
#include "core/kstring.h"
#include "core/logger.h"
#include "math/kmath.h"
#include "renderer_backend.h"
#include "resources/resource_types.h"
#include "systems/texture_system.h"
#include "systems/material_system.h"

typedef struct renderer_system_state {
    renderer_backend backend;
    mat4 projection;
    mat4 view;
    f32 near_clip;
    f32 far_clip;
    material* test_material;
} renderer_system_state;

static renderer_system_state* state_ptr;

// TODO: temp
b8 event_on_debug_event(u16 code, void* sender, void* listener_inst, event_context data) {
    const char* names[3] = {
        "cobblestone",
        "paving",
        "paving2"};
    static i8 choice = 2;

    const char* old_name = names[choice];
    choice++;
    choice %= 3;

    // Load up the new texture.
    state_ptr->test_material->diffuse_map.texture = texture_system_acquire(names[choice], true);
    if (!state_ptr->test_material->diffuse_map.texture) {
        KWARN("event_on_debug_event no texture! using default");
        state_ptr->test_material->diffuse_map.texture = texture_system_get_default_texture();
    }
    texture_system_release(old_name);
    return true;
}
// TODO: end temp

b8 renderer_system_initialize(u64* memory_requirement, void* state, const char* application_name) {
    *memory_requirement = sizeof(renderer_system_state);
    if (state == 0) {
        return true;
    }
    state_ptr = state;

    // TODO: temp
    event_register(EVENT_CODE_DEBUG0, state_ptr, event_on_debug_event);
    // TODO: end temp

    // TODO: make this configurable.
    renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, &state_ptr->backend);
    state_ptr->backend.frame_number = 0;

    if (!state_ptr->backend.initialize(&state_ptr->backend, application_name)) {
        KFATAL("Renderer backend failed to initialize. Shutting down.");
        return false;
    }

    state_ptr->near_clip = 0.1f;
    state_ptr->far_clip = 1000.0f;
    state_ptr->projection = mat4_perspective(deg_to_rad(45.0f), 1280 / 720.0f, state_ptr->near_clip, state_ptr->far_clip);

    state_ptr->view = mat4_translation((vec3){0, 0, 30.0f});
    state_ptr->view = mat4_inverse(state_ptr->view);
    
    return true;
}

void renderer_system_shutdown(void* state) {
    if (state_ptr) {
        // TODO: temp
        event_unregister(EVENT_CODE_DEBUG0, state_ptr, event_on_debug_event);
        // TODO: end temp
        state_ptr->backend.shutdown(&state_ptr->backend);
    }

    state_ptr = 0;
}

b8 renderer_begin_frame(f32 delta_time) {
    if (!state_ptr) {
        return false;
    }
    return state_ptr->backend.begin_frame(&state_ptr->backend, delta_time);
}

b8 renderer_end_frame(f32 delta_time) {
    if (!state_ptr) {
        return false;
    }
    b8 result = state_ptr->backend.end_frame(&state_ptr->backend, delta_time);
    state_ptr->backend.frame_number++;
    return result;
}

void renderer_on_resized(u16 width, u16 height) {
    if (state_ptr) {
        state_ptr->projection = mat4_perspective(deg_to_rad(45.0f), width / (f32)height, state_ptr->near_clip, state_ptr->far_clip);
        state_ptr->backend.resized(&state_ptr->backend, width, height);
    } else {
        KWARN("renderer backend does not exist to accept resize: %i %i", width, height);
    }
}

b8 renderer_draw_frame(render_packet* packet) {
    if (renderer_begin_frame(packet->delta_time)) {
        state_ptr->backend.update_global_state(state_ptr->projection, state_ptr->view, vec3_zero(), vec4_one(), 0);

        mat4 model = mat4_translation((vec3){0, 0, 0});
        geometry_render_data data = {};
        data.model = model;

        if (!state_ptr->test_material) {
            state_ptr->test_material = material_system_acquire("test_material");
            if (!state_ptr->test_material) {
                KWARN("Automatic material load failed, falling back to manual default material.");
                // Manual config
                material_config config;
                string_ncopy(config.name, "test_material", MATERIAL_NAME_MAX_LENGTH);
                config.auto_release = false;
                config.diffuse_colour = vec4_one();  // white
                string_ncopy(config.diffuse_map_name, DEFAULT_TEXTURE_NAME, TEXTURE_NAME_MAX_LENGTH);
                state_ptr->test_material = material_system_acquire_from_config(config);
            }
        }
        data.material = state_ptr->test_material;
        state_ptr->backend.update_object(data);

        b8 result = renderer_end_frame(packet->delta_time);

        if (!result) {
            KERROR("renderer_end_frame failed. Application shutting down...");
            return false;
        }
    }

    return true;
}

void renderer_set_view(mat4 view) {
    state_ptr->view = view;
}

void renderer_create_texture(const u8* pixels, struct texture* texture) {
    state_ptr->backend.create_texture(pixels, texture);
}

void renderer_destroy_texture(struct texture* texture) {
    state_ptr->backend.destroy_texture(texture);
}

b8 renderer_create_material(struct material* material) {
    return state_ptr->backend.create_material(material);
}

void renderer_destroy_material(struct material* material) {
    state_ptr->backend.destroy_material(material);
}