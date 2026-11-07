/**
 * @file render_view_ui.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Provides an interface to the render view for the world.
 * @version 1.0
 * @date 2022-06-10
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "defines.h"

#include "renderer/renderer_types.inl"

b8 render_view_world_on_create(struct render_view* self);

void render_view_world_on_destroy(struct render_view* self);

void render_view_world_on_resize(struct render_view* self, u32 width, u32 height);

b8 render_view_world_on_build_packet(const struct render_view* self, void* data, struct render_view_packet* out_packet);

b8 render_view_world_on_render(const struct render_view* self, const struct render_view_packet* packet, u64 frame_number, u64 render_target_index);
