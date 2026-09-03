/**
 * @file math_types.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Contains various math types required for the engine.
 * @version 1.0
 * @date 2022-01-10
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "defines.h"

/**
 * @brief A 2-element vector. 
*/
typedef union vec2_u
{
    // An array of x, y.
    f32 elements[2];

    struct
    {
        union
        {
            /**
             * @brief The first element. 
            */
            f32 x, r, s, u;
        };

        union
        {
            /**
             * @brief The second element.
             */
            f32 y, g, t, v;
        };
    };
} vec2;

/**
 * @brief A 3-element vector. 
*/
typedef union vec3_u
{
    /**
     * @brief An array of x, y, z.
     */
    f32 elements[3];

    struct
    {
        union
        {
            /**
             * @brief The first element.
            */
            f32 x, r, s, u;
        };

        union
        {
            /**
             * @brief The second element.
            */
            f32 y, g, t, v;
        };

        union
        {
            /**
             * @brief The third element.
             */
            f32 z, b, p, w;
        };
    };
} vec3;

/**
 * @brief A 4-element vector. 
*/
typedef union vec4_u
{
    /**
     * @brief An array of x, y, z, w.
    */
    f32 elements[4];

    union
    {
        struct
        {
            union
            {
                /**
                 * @brief The first element.
                */
                f32 x, r, s;
            };

            union
            {
                /**
                 * @brief The second element.
                */
                f32 y, g, t;
            };

            union
            {
                /**
                 * @brief The third element.
                */
                f32 z, b, p;
            };

            union
            {
                /**
                 * @brief The fourth element.
                */
                f32 w, a, q;
            };
        };
    };
} vec4;

/**
 * @brief A quaternion, used to represent rotational orientation.
*/
typedef vec4 quat;

/**
 * @brief A 4x4 matrix, typically used to represent object transformations.
*/
typedef union mat4_u
{
    /**
     * @brief The matrix elements.
    */
    f32 data[16];
} mat4;

/**
 * @brief Represents a single vertex in 3D space. 
*/
typedef struct vertex_3d
{
    /**
     * @brief The position of the vertex.
    */
    vec3 position;

    /**
     * @brief The texture coordinate of the vertex.
    */
    vec2 texcoord;
} vertex_3d;

/**
 * @brief Represents a single vertex in 2D space.
*/
typedef struct vertex_2d
{
    /**
     * @brief The position of the vertex.
    */
    vec2 position;

    /**
     * @brief The texture coordinate of the vertex.
    */
    vec2 texcoord;
} vertex_2d;
