#ifndef SCENE_MESH_H
#define SCENE_MESH_H

#include "s-block.h"

typedef struct _mesh_block {
  block meta;
  float* vertices; uint64_t n_vertices;
  float* normals; uint64_t n_normals;
  float* texcoords; uint64_t n_texcoords;
  float* colors; uint64_t n_colors;
  uint32_t* indices; uint64_t n_indices;
} blk_mesh;

blk_mesh* alloc_mesh_block();

#endif /* SCENE_MESH_H */
