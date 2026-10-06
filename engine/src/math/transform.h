/**
 * @file transform.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Contains functions to manipulate transforms.
 * @version 1.0
 * @date 2022-01-10
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#include "math_types.h"

/**
 * @brief Creates and returns a new transform, using a zero
 * vector for position, identity quaternion for rotation, and
 * a one vector for scale. Also has a null parent. Marked dirty
 * by default.
*/
KAPI transform transform_create();

/**
 * @brief Creates a transform from the given position.
 * Uses a zero rotation and a one scale.
 * 
 * @param position The position to be used.
 * @returns A new transform.
*/
KAPI transform transform_from_position(vec3 position);

/**
 * @brief Creates a transform from the given rotation.
 * Uses a zero position and a one scale.
 * 
 * @param rotation The rotation to be used.
 * @returns A new transform.
*/
KAPI transform transform_from_rotation(quat rotation);

/**
 * @brief Creates a transform from the given position and rotation.
 * Uses a one scale.
 * 
 * @param position The position to be used.
 * @param rotation The rotation to be used.
 * @returns A new transform.
*/
KAPI transform transform_from_position_rotation(vec3 position, quat rotation);

/**
 * @brief Creates a transform from the given position, rotation and scale.
 * 
 * @param position The position to be used.
 * @param rotation The rotation to be used.
 * @param scale The scale to be used.
 * @returns A new transform.
*/
KAPI transform transform_from_position_rotation_scale(vec3 position, quat rotation, vec3 scale);

/**
 * @brief Returns a pointer to the provided transform's parent.
 * 
 * @param child A pointer to the transform whose parent to retrieve.
 * @returns A pointer to the parent transform.
*/
KAPI transform* transform_get_parent(transform* child);

/**
 * @brief Sets the parent of the provided transform.
 * 
 * @param child A pointer to the transform whose parent will be set.
 * @param parent A pointer to the parent transform.
*/
KAPI void transform_set_parent(transform* child, transform* parent);

/**
 * @brief Returns the position of the given transform.
 * 
 * @param transform A constant pointer whose position to get.
 * @returns A copy of the position.
*/
KAPI vec3 transform_get_position(const transform* transform);

/**
 * @brief Sets the position of the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param position The position to be set.
*/
KAPI void transform_set_position(transform* transform, vec3 position);

/**
 * @brief Applies a translation to the given transform. Not the
 * same as setting.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param translation The translation to be applied.
*/
KAPI void transform_translate(transform* transform, vec3 translation);

/**
 * @brief Returns the rotation of the given transform.
 * 
 * @param transform A constant pointer whose rotation to get.
 * @returns A copy of the rotation.
*/
KAPI quat transform_get_rotation(const transform* transform);

/**
 * @brief Sets the rotation of the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param rotation The rotation to be set.
*/
KAPI void transform_set_rotation(transform* transform, quat rotation);

/**
 * @brief Applies a rotation to the given transform. Not the
 * same as setting.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param rotation The rotation to be applied.
*/
KAPI void transform_rotate(transform* transform, quat rotation);

/**
 * @brief Returns the scale of the given transform.
 * 
 * @param transform A constant pointer whose scale to get.
 * @returns A copy of the scale.
*/
KAPI vec3 transform_get_scale(const transform* transform);

/**
 * @brief Sets the scale of the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param scale The scale to be set.
*/
KAPI void transform_set_scale(transform* transform, vec3 scale);

/**
 * @brief Applies a scale to the given transform. Not the
 * same as setting.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param scale The scale to be applied.
*/
KAPI void transform_scale(transform* transform, vec3 scale);

/**
 * @brief Sets the position and rotation of the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param position The position to be set.
 * @param rotation The rotation to be set.
*/
KAPI void transform_set_position_rotation(transform* transform, vec3 position, quat rotation);

/**
 * @brief Sets the position, rotation and scale of the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param position The position to be set.
 * @param rotation The rotation to be set.
 * @param scale The scale to be set.
*/
KAPI void transform_set_position_rotation_scale(transform* transform, vec3 position, quat rotation, vec3 scale);

/**
 * @brief Applies translation and rotation to the given transform.
 * 
 * @param transform A pointer to the transform to be updated.
 * @param translation The translation to be applied.
 * @param rotation The rotation to be applied.
*/
KAPI void transform_translate_rotate(transform* transform, vec3 translation, quat rotation);

/**
 * @brief Retrieves the local transformation matrix from the provided transform.
 * Automatically recalculates the matrix if it is dirty. Otherwise, the already
 * calculated one is returned.
 * 
 * @param transform A pointer to the transform whose matrix to retrieve.
 * @returns A copy of the local transformation matrix.
*/
KAPI mat4 transform_get_local(transform* transform);

/**
 * @brief Obtains the world matrix of the given transform
 * by examining its parent (if there is one) and multiplying it
 * against the local matrix.
 * 
 * @param transform A pointer to the transform whose world matrix to retrieve.
 * @returns A copy of the world matrix.
*/
KAPI mat4 transform_get_world(transform* transform);
