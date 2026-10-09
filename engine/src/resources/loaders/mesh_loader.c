#include "mesh_loader.h"
#include "loader_utils.h"

#include "core/logger.h"
#include "core/kmemory.h"
#include "core/kstring.h"
#include "containers/darray.h"
#include "resources/resource_types.h"
#include "systems/resource_system.h"
#include "systems/geometry_system.h"
#include "math/kmath.h"
#include "math/geometry_utils.h"
#include "platform/filesystem.h"

#include <stdio.h>  //sscanf

#define SUPPORTED_FILETYPE_COUNT 2

typedef enum mesh_file_type
{
    MESH_FILE_TYPE_NOT_FOUND,
    MESH_FILE_TYPE_KSM,
    MESH_FILE_TYPE_OBJ
} mesh_file_type;

typedef struct supported_mesh_filetype
{
    char* extension;
    mesh_file_type type;
    b8 is_binary;
} supported_mesh_filetype;

typedef struct mesh_vertex_index_data
{
    u32 position_index;
    u32 normal_index;
    u32 texcoord_index;
} mesh_vertex_index_data;

typedef struct mesh_face_data
{
    mesh_vertex_index_data vertices[3];
} mesh_face_data;

typedef struct mesh_group_data
{
    // Darray.
    mesh_face_data* faces;
} mesh_group_data;

/**
 * @brief Imports an obj file. This reads the obj, creates geometry configs, then calls logic to write
 * those geometries out to a binary ksm file. That file can be used on the next load.
 * 
 * @param obj_file A pointer to the obj file handle to be read.
 * @param out_ksm_filename The path to the ksm file to be written to.
 * @param out_geometries_darray A darray of geometries parsed from the file.
 * @returns true on success; otherwise false.
*/
b8 import_obj_file(file_handle* obj_file, const char* out_ksm_filename, geometry_config** out_geometries_darray);

void process_subobject(vec3* positions, vec3* normals, vec2* tex_coords, mesh_face_data* faces, geometry_config* out_data);

b8 import_obj_material_library_file(const char* mtl_file_path);

b8 load_ksm_file(file_handle* ksm_file, geometry_config** out_geometries_darray);

b8 write_ksm_file(const char* path, const char* name, u32 geometry_count, geometry_config** geometries);

b8 write_kmt_file(const char* directory, material_config* config);

b8 mesh_loader_load(struct resource_loader* self, const char* name, resource* out_resource)
{
    if (!self || !name || !out_resource)
    {
        return false;
    }

    char* format_str = "%s/%s/%s%s";
    file_handle f;

    // Supported extensions. Note that these are in order of priority when looked up.
    // This is to prioritize the loading of a binary version of the mesh, followed by
    // importing various types of meshes to binary types, which would be loaded on the
    // next run.
    // TODO: Might be good to be able to specify an override to always import (i.e. skip
    // binary versions) for debug purposes.
    supported_mesh_filetype supported_filetypes[SUPPORTED_FILETYPE_COUNT];
    supported_filetypes[0] = (supported_mesh_filetype){".ksm", MESH_FILE_TYPE_KSM, true,};
    supported_filetypes[1] = (supported_mesh_filetype){".obj", MESH_FILE_TYPE_OBJ, false};

    char full_file_path[512];
    mesh_file_type type = MESH_FILE_TYPE_NOT_FOUND;

    // Try each supported extension.
    for (u32 i = 0; i < SUPPORTED_FILETYPE_COUNT; ++i)
    {
        string_format(full_file_path, format_str, resource_system_get_base_path(), self->type_path, name, supported_filetypes[i].extension);

        // If the file exists, open it and stop looking.
        if (filesystem_exists(full_file_path))
        {
            if (filesystem_open(full_file_path, FILE_MODE_READ, supported_filetypes[i].is_binary, &f))
            {
                type = supported_filetypes[i].type;
                break;
            }
        }
    }

    if (type == MESH_FILE_TYPE_NOT_FOUND)
    {
        KERROR("Unable to find mesh of supported type called '%s'!", name);
        return false;
    }

    out_resource->full_path = string_duplicate(full_file_path);

    // The resource data is just an array of configs.
    geometry_config* resource_data = darray_create(geometry_config);

    b8 result = false;

    switch (type)
    {
        case MESH_FILE_TYPE_OBJ:
        {
            // Generate the ksm filename.
            char ksm_file_name[512];
            string_format(ksm_file_name, "%s/%s/%s%s", resource_system_get_base_path(), self->type_path, name, ".ksm");
            result = import_obj_file(&f, ksm_file_name, &resource_data);
            break;
        }
        case MESH_FILE_TYPE_KSM:
            result = load_ksm_file(&f, &resource_data);
            break;
        default:
        case MESH_FILE_TYPE_NOT_FOUND:
            KERROR("Unable to find mesh of supported type called '%s'!", name);
            break;
    }

    filesystem_close(&f);

    if (!result)
    {
        KERROR("Failed to process mesh file '%s'!", full_file_path);
        darray_destroy(resource_data);

        out_resource->data = 0;
        out_resource->data_size = 0;
        return false;
    }

    out_resource->data = resource_data;

    // Use the data size as a count.
    out_resource->data_size = darray_length(resource_data);

    return true;
}

void mesh_loader_unload(struct resource_loader* self, resource* resource)
{
    u32 count = darray_length(resource->data);

    for (u32 i = 0; i < count; ++i)
    {
        geometry_config* config = &((geometry_config*)resource->data)[i];

        geometry_system_config_dispose(config);
    }

    darray_destroy(resource->data);

    resource->data = 0;
    resource->data_size = 0;
}

b8 load_ksm_file(file_handle* ksm_file, geometry_config** out_geometries_darray)
{
    // TODO: Read ksm file.
    return true;
}

b8 write_ksm_file(const char* path, const char* name, u32 geometry_count, geometry_config** geometries)
{
    // TODO: Write out ksm binary file.
    return true;
}

b8 import_obj_file(file_handle* obj_file, const char* out_ksm_filename, geometry_config** out_geometries_darray)
{
    // Positions.
    vec3* positions = darray_reserve(vec3, 16384);

    // Normals.
    vec3* normals = darray_reserve(vec3, 16384);

    // Texcoords.
    vec2* tex_coords = darray_reserve(vec2, 16384);

    // Groups.
    mesh_group_data* groups = darray_reserve(mesh_group_data, 4);

    char material_file_name[512] = "";

    char name[512];
    u8 current_mat_name_count = 0;
    char material_names[32][64];

    char line_buf[512] = "";
    char* p = &line_buf[0];
    u64 line_length = 0;

    // Index 0 is previous, 1 is previous before that.
    char prev_first_chars[2] = {0, 0};

    while (true)
    {
        if (!filesystem_read_line(obj_file, 511, &p, &line_length))
        {
            break;
        }

        // Skip blank lines.
        if (line_length < 1)
        {
            continue;
        }

        char first_char = line_buf[0];

        switch (first_char)
        {
            case '#':
                // Skip comments.
                continue;
            case 'v':
            {
                char second_char = line_buf[1];

                switch (second_char)
                {
                    case ' ':
                    {
                        // Vertex position.
                        vec3 pos;
                        char t[2];

                        sscanf(
                            line_buf,
                            "%s %f %f %f",
                            t,
                            &pos.x,
                            &pos.y,
                            &pos.z
                        );

                        darray_push(positions, pos);
                    }
                    break;
                    case 'n':
                    {
                        // Vertex normal.
                        vec3 norm;
                        char t[2];

                        sscanf(
                            line_buf,
                            "%s %f %f %f",
                            t,
                            &norm.x,
                            &norm.y,
                            &norm.z
                        );

                        darray_push(normals, norm);
                    }
                    break;
                    case 't':
                    {
                        // Vertex texture coords.
                        vec2 tex_coord;
                        char t[2];

                        // NOTE: Ignoring Z if present.
                        sscanf(
                            line_buf,
                            "%s %f %f",
                            t,
                            &tex_coord.x,
                            &tex_coord.y
                        );

                        darray_push(tex_coords, tex_coord);
                    }
                    break;
                }
            }
            break;
            case 's':
            {

            }
            break;
            case 'f':
            {
                // Face.
                // f 1/1/1 2/2/2 3/3/3 = pos/tex/norm pos/tex/norm pos/tex/norm

                mesh_face_data face;
                char t[2];

                u64 normal_count = darray_length(normals);
                u64 tex_coord_count = darray_length(tex_coords);

                if (normal_count == 0 || tex_coord_count == 0)
                {
                    sscanf(
                        line_buf,
                        "%s %d %d %d",
                        t,
                        &face.vertices[0].position_index,
                        &face.vertices[1].position_index,
                        &face.vertices[2].position_index
                    );
                }
                else
                {
                    sscanf(
                        line_buf,
                        "%s %d/%d/%d %d/%d/%d %d/%d/%d",
                        t,
                        &face.vertices[0].position_index,
                        &face.vertices[0].texcoord_index,
                        &face.vertices[0].normal_index,

                        &face.vertices[1].position_index,
                        &face.vertices[1].texcoord_index,
                        &face.vertices[1].normal_index,

                        &face.vertices[2].position_index,
                        &face.vertices[2].texcoord_index,
                        &face.vertices[2].normal_index
                    );
                }

                u64 group_index = darray_length(groups) - 1;

                darray_push(groups[group_index].faces, face);
            }
            break;
            case 'm':
            {
                // Material Library file.
                char substr[7];
            }
        }
    }
}
