/**
 * @file mesh.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief Provides an interface for loading and unloading meshes.
 * @version 1.0
 * @date 2022-08-11
 * 
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
*/

#pragma once

#include "resource_types.h"

/**
 * @brief Loads a mesh from a resource.
 * 
 * @param resource_name The name of the mesh resource to load.
 * @param out_mesh A pointer to the mesh.
 * @returns true if successful; otherwise false.
*/
b8 mesh_load_from_resource(const char* resource_name, mesh* out_mesh);

/**
 * @brief Unloads a mesh.
 * 
 * @param mesh A pointer to the mesh to unload.
*/
void mesh_unload(mesh* mesh);
