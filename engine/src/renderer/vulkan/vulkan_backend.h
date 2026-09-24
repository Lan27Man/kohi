/**
 * @file vulkan_backend.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief This file contains the Vulkan implementation of the renderer backend.
 * All Vulkan calls are made behind this facade to keep the rest of the engine
 * unaware about the inner workings of Vulkan.
 * @version 1.0
 * @date 2022-01-11
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "renderer/renderer_backend.h"
#include "resources/resource_types.h"

struct shader;
struct shader_uniform;

/**
 * @brief Initializes the Vulkan backend.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param application_name The name of the application.
 * @returns true if initialized successfully; otherwise false.
*/
b8 vulkan_renderer_initialize(renderer_backend* backend, const char* application_name);

/**
 * @brief Shuts the Vulkan renderer backend down.
 * 
 * @param backend A pointer to the generic backend interface.
*/
void vulkan_renderer_shutdown(renderer_backend* backend);

/**
 * @brief Handles window resizes.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param width The new window width.
 * @param height The new window height.
*/
void vulkan_renderer_on_resized(renderer_backend* backend, u16 width, u16 height);

/**
 * @brief Performs setup routines required at the start of a frame.
 * @note A false result does not necessarily indicate failure. It can also specify that
 * the backend is simply not in a state capable of drawing a frame at the moment, and
 * that it should be attempted again on the next loop. End frame does not need to (and
 * should not) be called if this is the case.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param delta_time The time in seconds since the last frame.
 * @returns true if successful; otherwise false.
*/
b8 vulkan_renderer_begin_frame(renderer_backend* backend, f32 delta_time);

/**
 * @brief Performs routines required to draw a frame, such as presentation. Should only be called
 * after a successful return of begin_frame.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param delta_time The time in seconds since the last frame.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_end_frame(renderer_backend* backend, f32 delta_time);

/**
 * @brief Begins a renderpass with the given id.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param renderpass_id The identifier of the renderpass to begin.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_begin_renderpass(struct renderer_backend* backend, u8 renderpass_id);

/**
 * @brief Ends a renderpass with the given id.
 * 
 * @param backend A pointer to the generic backend interface.
 * @param renderpass_id The identifier of the renderpass to end.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_end_renderpass(struct renderer_backend* backend, u8 renderpass_id);

/**
 * @brief Draws the given geometry. Should only be called inside a renderpass, within a frame.
 * 
 * @param data The render data of the geometry to be drawn.
*/
void vulkan_renderer_draw_geometry(geometry_render_data data);

/**
 * @brief Creates a Vulkan-specific texture, acquiring internal resources as needed.
 * 
 * @param pixels The raw image data used for the texture.
 * @param texture A pointer to the texture to hold the resources.
*/
void vulkan_renderer_create_texture(const u8* pixels, texture* texture);

/**
 * @brief Destroys the given texture, releasing internal resources.
 * 
 * @param texture A pointer to the texture to be destroyed.
*/
void vulkan_renderer_destroy_texture(texture* texture);

/**
 * @brief Creates Vulkan-specific internal resources for the given geometry using
 * the data provided.
 * 
 * @param geometry A pointer to the geometry to be created.
 * @param vertex_size The size of a single vertex.
 * @param vertex_count The total number of vertices.
 * @param vertices An array of vertices.
 * @param index_size The size of an individual index.
 * @param index_count The total number of indices.
 * @param indices An array of indices.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_create_geometry(geometry* geometry, u32 vertex_size, u32 vertex_count, const void* vertices, u32 index_size, u32 index_count, const void* indices);

/**
 * @brief Destroys the given geometry, releasing internal resources.
 * 
 * @param geometry A pointer to the geometry to be destroyed.
*/
void vulkan_renderer_destroy_geometry(geometry* geometry);

/**
 * @brief Creates internal shader resources using the provided parameters.
 * 
 * @param shader A pointer to the shader.
 * @param renderpass_id The identifier of the renderpass to be associated with the shader.
 * @param stage_count The total number of stages.
 * @param stage_filenames An array of shader stage filenames to be loaded. Should align with stages array.
 * @param stages An array of shader_stages indicating what render stages (vertex, fragment, etc.) are used in this shader.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_create(struct shader* shader, u8 renderpass_id, u8 stage_count, const char** stage_filenames, shader_stage* stages);

/**
 * @brief Destroys the given shader and releases any resources held by it.
 * 
 * @param shader A pointer to the shader to be destroyed.
*/
void vulkan_renderer_shader_destroy(struct shader* shader);

/**
 * @brief Initializes a configured shader. Will be automatically destroyed if this step fails.
 * Must be done after shader_create().
 * 
 * @param shader A pointer to the shader to be initialized.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_initialize(struct shader* shader);

/**
 * @brief Uses the given shader, activating it for updates to attributes, uniforms and such,
 * and for use in draw calls.
 * 
 * @param shader A pointer to the shader to be used.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_use(struct shader* shader);

/**
 * @brief Binds global resources for use and updating.
 * 
 * @param shader A pointer to the shader whose globals are to be bound.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_bind_globals(struct shader* shader);

/**
 * @brief Binds instance resources for use and updating.
 * 
 * @param shader A pointer to the shader whose instance resources are to be bound.
 * @param instance_id The identifier of the instance to be bound.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_bind_instance(struct shader* shader, u32 instance_id);

/**
 * @brief Applies global data to the uniform buffer.
 * 
 * @param shader A pointer to the shader to apply the global data for.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_apply_globals(struct shader* shader);

/**
 * @brief Applies data for the currently bound instance.
 * 
 * @param shader A pointer to the shader to apply the instance data for.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_apply_instance(struct shader* shader);

/**
 * @brief Acquires internal instance-level resources and provides an instance id.
 * 
 * @param shader A pointer to the shader to acquire resources from.
 * @param out_instance_id A pointer to hold the new instance identifier.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_acquire_instance_resources(struct shader* shader, u32* out_instance_id);

/**
 * @brief Releases internal instance-level resources for the given instance id.
 * 
 * @param shader A pointer to the shader to release resources from.
 * @param instance_id The instance identifier whose resources are to be released.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_shader_release_instance_resources(struct shader* shader, u32 instance_id);

/**
 * @brief Sets the uniform of the given shader to the provided value.
 * 
 * @param shader A pointer to the shader.
 * @param uniform A constant pointer to the uniform.
 * @param value A pointer to the value to be set.
 * @returns true on success; otherwise false.
*/
b8 vulkan_renderer_set_uniform(struct shader* shader, struct shader_uniform* uniform, const void* value);
