#include "camera.h"

#include "math/kmath.h"

camera camera_create()
{
    camera c;

    camera_reset(&c);

    return c;
}

void camera_reset(camera* camera)
{
    if (camera)
    {
        camera->euler_rotation = vec3_zero();
        camera->position = vec3_zero();
        camera->is_dirty = false;
        camera->view_matrix = mat4_identity();
    }
}

vec3 camera_position_get(const camera* camera)
{
    if (camera)
    {
        return camera->position;
    }

    return vec3_zero();
}

void camera_position_set(camera* camera, vec3 position)
{
    if (camera)
    {
        camera->position = position;
        camera->is_dirty = true;
    }
}

vec3 camera_rotation_euler_get(const camera* camera)
{
    if (camera)
    {
        return camera->euler_rotation;
    }

    return vec3_zero();
}

void camera_rotation_euler_set(camera* camera, vec3 rotation)
{
    if (camera)
    {
        camera->euler_rotation = rotation;
        camera->is_dirty = true;
    }
}

mat4 camera_view_get(camera* camera)
{
    if (camera)
    {
        if (camera->is_dirty)
        {
            mat4 rotation = mat4_euler_xyz(camera->euler_rotation.x, camera->euler_rotation.y, camera->euler_rotation.z);
            mat4 translation = mat4_translation(camera->position);

            camera->view_matrix = mat4_mul(rotation, translation);
            camera->view_matrix = mat4_inverse(camera->view_matrix);
            camera->is_dirty = false;
        }

        return camera->view_matrix;
    }

    return mat4_identity();
}

vec3 camera_forward(camera* camera)
{
    if (camera)
    {
        mat4 view = camera_view_get(camera);

        return mat4_forward(view);
    }

    return vec3_zero();
}

vec3 camera_backward(camera* camera)
{
    if (camera)
    {
        mat4 view = camera_view_get(camera);

        return mat4_backward(view);
    }

    return vec3_zero();
}

vec3 camera_left(camera* camera)
{
    if (camera)
    {
        mat4 view = camera_view_get(camera);

        return mat4_left(view);
    }

    return vec3_zero();
}

vec3 camera_right(camera* camera)
{
    if (camera)
    {
        mat4 view = camera_view_get(camera);

        return mat4_right(view);
    }

    return vec3_zero();
}

void camera_move_forward(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = camera_forward(camera);
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_move_backward(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = camera_backward(camera);
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_move_left(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = camera_left(camera);
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_move_right(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = camera_right(camera);
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_move_up(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = vec3_up();
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_move_down(camera* camera, f32 amount)
{
    if (camera)
    {
        vec3 direction = vec3_down();
        direction = vec3_mul_scalar(direction, amount);

        camera->position = vec3_add(camera->position, direction);
        camera->is_dirty = true;
    }
}

void camera_yaw(camera* camera, f32 amount)
{
    if (camera)
    {
        camera->euler_rotation.y += amount;
        camera->is_dirty = true;
    }
}

void camera_pitch(camera* camera, f32 amount)
{
    if (camera)
    {
        camera->euler_rotation.x += amount;

        // Clamp to avoid Gimball lock.
        static const f32 limit = 1.55334306f;   // 89 degrees, or equivalent to deg_to_rad(89.0f);

        camera->euler_rotation.x = KCLAMP(camera->euler_rotation.x, -limit, limit);
        camera->is_dirty = true;
    }
}
