#include "transform.h"
#include "kmath.h"

transform transform_create()
{
    transform t;

    transform_set_position_rotation_scale(&t, vec3_zero(), quat_identity(), vec3_one());

    t.local = mat4_identity();
    t.parent = 0;

    return t;
}

transform transform_from_position(vec3 position)
{
    transform t;

    transform_set_position_rotation_scale(&t, position, quat_identity(), vec3_one());

    t.local = mat4_identity();
    t.parent = 0;

    return t;
}

transform transform_from_rotation(quat rotation)
{
    transform t;

    transform_set_position_rotation_scale(&t, vec3_zero(), rotation, vec3_one());

    t.local = mat4_identity();
    t.parent = 0;

    return t;
}

transform transform_from_position_rotation(vec3 position, quat rotation)
{
    transform t;

    transform_set_position_rotation_scale(&t, position, rotation, vec3_one());

    t.local = mat4_identity();
    t.parent = 0;

    return t;
}

transform transform_from_position_rotation_scale(vec3 position, quat rotation, vec3 scale)
{
    transform t;

    transform_set_position_rotation_scale(&t, position, rotation, scale);

    t.local = mat4_identity();
    t.parent = 0;

    return t;
}

transform* transform_get_parent(transform* child)
{
    if (!child)
    {
        return 0;
    }

    return child->parent;
}

void transform_set_parent(transform* child, transform* parent)
{
    if (child)
    {
        child->parent = parent;
    }
}

vec3 transform_get_position(const transform* transform)
{
    return transform->position;
}

void transform_set_position(transform* transform, vec3 position)
{
    transform->position = position;
    transform->is_dirty = true;
}

void transform_translate(transform* transform, vec3 translation)
{
    transform->position = vec3_add(transform->position, translation);
    transform->is_dirty = true;
}

quat transform_get_rotation(const transform* transform)
{
    return transform->rotation;
}

void transform_set_rotation(transform* transform, quat rotation)
{
    transform->rotation = rotation;
    transform->is_dirty = true;
}

void transform_rotate(transform* transform, quat rotation)
{
    transform->rotation = quat_mul(transform->rotation, rotation);
    transform->is_dirty = true;
}

vec3 transform_get_scale(const transform* transform)
{
    return transform->scale;
}

void transform_set_scale(transform* transform, vec3 scale)
{
    transform->scale = scale;
    transform->is_dirty = true;
}

void transform_scale(transform* transform, vec3 scale)
{
    transform->scale = vec3_mul(transform->scale, scale);
    transform->is_dirty = true;
}

void transform_set_position_rotation(transform* transform, vec3 position, quat rotation)
{
    transform->position = position;
    transform->rotation = rotation;
    transform->is_dirty = true;
}

void transform_set_position_rotation_scale(transform* transform, vec3 position, quat rotation, vec3 scale)
{
    transform->position = position;
    transform->rotation = rotation;
    transform->scale = scale;
    transform->is_dirty = true;
}

void transform_translate_rotate(transform* transform, vec3 translation, quat rotation)
{
    transform->position = vec3_add(transform->position, translation);
    transform->rotation = quat_mul(transform->rotation, rotation);
    transform->is_dirty = true;
}

mat4 transform_get_local(transform* transform)
{
    if (transform)
    {
        if (transform->is_dirty)
        {
            mat4 tr = mat4_mul(quat_to_mat4(transform->rotation), mat4_translation(transform->position));
            tr = mat4_mul(mat4_scale(transform->scale), tr);

            transform->local = tr;
            transform->is_dirty = false;
        }

        return transform->local;
    }

    return mat4_identity();
}

mat4 transform_get_world(transform* transform)
{
    if (transform)
    {
        mat4 l = transform_get_local(transform);

        if (transform->parent)
        {
            mat4 p = transform_get_world(transform->parent);

            return mat4_mul(l, p);
        }

        return l;
    }

    return mat4_identity();
}
