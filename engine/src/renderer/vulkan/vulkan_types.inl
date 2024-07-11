#pragma once

#include <vulkan/vulkan.h>

#include "core/asserts.h"
#include "defines.h"

#define VK_CHECK(expr)               \
    {                                \
        KASSERT(expr == VK_SUCCESS); \
    }

typedef struct vulkan_context {
    VkInstance instance;
    VkAllocationCallbacks* allocator;

#if defined(_DEBUG)
    VkDebugUtilsMessengerEXT debug_messenger;
#endif
} vulkan_context;

