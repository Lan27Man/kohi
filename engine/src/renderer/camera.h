/**
 * @file camera.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief This file contains an implementation of a camera.
 * @version 1.0
 * @date 2022-05-21
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "math/math_types.h"

/**
 * @brief Represents a camera that can be used for
 * a variety of things, especially rendering. Ideally
 * these are created and managed by the camera system.
*/
typedef struct camera
{
    /**
     * @brief The position of this camera.
     * NOTE: Do not set this directly, use camera_position_set() instead
     * so the view matrix is recalculated when needed.
    */
    vec3 position;

    /**
     * @brief The rotation of this camera using Euler angles (pitch, yaw, roll).
     * NOTE: Do not set this directly, use camera_rotation_euler_set() instead
     * so the view matrix is recalculated when needed.
    */
    vec3 euler_rotation;

    /**
     * @brief Internal flag used to determine when the view matrix needs to be rebuilt.
    */
    b8 is_dirty;

    /**
     * @brief The view matrix of this camera.
     * NOTE: IMPORTANT: Do not get this directly, use camera_view_get() instead
     * so the view matrix is recalculated when needed.
    */
    mat4 view_matrix;
} camera;

/**
 * @brief Creates a new camera with default zero position
 * and rotation, and view identity matrix. Ideally, the
 * camera system should be used to create this instead
 * of doing so directly.
 * 
 * @returns A copy of a newly-created camera.
*/
camera camera_create();

/**
 * @brief Defaults the provided camera to default zero
 * rotation and position, and view matrix to identity.
 * 
 * @param camera A pointer to the camera to be reset.
*/
void camera_reset(camera* camera);

/**
 * @brief Gets a copy of the camera's position.
 * 
 * @param camera A constant pointer to a camera.
 * @returns A copy of the camera's position.
*/
vec3 camera_position_get(const camera* camera);

/**
 * @brief Sets the provided camera's position.
 * 
 * @param camera A pointer to a camera.
 * @param position The position to be set.
*/
KAPI void camera_position_set(camera* camera, vec3 position);

/**
 * @brief Gets a copy of the camera's rotation in Euler angles.
 * 
 * @param camera A constant pointer to a camera.
 * @returns A copy of the camera's rotation in Euler angles.
*/
vec3 camera_rotation_euler_get(const camera* camera);

/**
 * @brief Sets the provided camera's rotation in Euler angles.
 * 
 * @param camera A pointer to a camera.
 * @param position The rotation in Euler angles to be set.
*/
void camera_rotation_euler_set(camera* camera, vec3 rotation);

/**
 * @brief Obtains a copy of the camera's view matrix. If camera is
 * dirty, a new one is created, set and returned.
 * 
 * @param camera A pointer to a camera.
 * @returns A copy of the up-to-date view matrix.
*/
mat4 camera_view_get(camera* camera);

/**
 * @brief Returns a copy of the camera's forward vector.
 * 
 * @param camera A pointer to a camera.
 * @returns A copy of the camera's forward vector.
*/
vec3 camera_forward(camera* camera);

/**
 * @brief Returns a copy of the camera's backward vector.
 * 
 * @param camera A pointer to a camera.
 * @returns A copy of the camera's backward vector.
*/
vec3 camera_backward(camera* camera);

/**
 * @brief Returns a copy of the camera's left vector.
 * 
 * @param camera A pointer to a camera.
 * @returns A copy of the camera's left vector.
*/
vec3 camera_left(camera* camera);

/**
 * @brief Returns a copy of the camera's right vector.
 * 
 * @param camera A pointer to a camera.
 * @returns A copy of the camera's right vector.
*/
vec3 camera_right(camera* camera);

/**
 * @brief Moves the camera forward by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_forward(camera* camera, f32 amount);

/**
 * @brief Moves the camera backward by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_backward(camera* camera, f32 amount);

/**
 * @brief Moves the camera left by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_left(camera* camera, f32 amount);

/**
 * @brief Moves the camera right by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_right(camera* camera, f32 amount);

/**
 * @brief Moves the camera up (straight along the y-axis) by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_up(camera* camera, f32 amount);

/**
 * @brief Moves the camera down (straight along the y-axis) by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to move.
*/
KAPI void camera_move_down(camera* camera, f32 amount);

/**
 * @brief Adjusts the camera's yaw by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to adjust by.
*/
KAPI void camera_yaw(camera* camera, f32 amount);

/**
 * @brief Adjusts the camera's pitch by the given amount.
 * 
 * @param camera A pointer to a camera.
 * @param amount The amount to adjust by.
*/
KAPI void camera_pitch(camera* camera, f32 amount);
