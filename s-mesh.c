#include <stdio.h>
#include <stdlib.h>
#include "s-mesh.h"

static void mesh_write(void* block, FILE*, uint64_t);
static void mesh_free(void* block);
static uint64_t mesh_size(void* block);

blk_mesh* alloc_mesh_block()
{
  blk_mesh* mesh = calloc(sizeof(blk_mesh), 1);
  mesh->meta.vtbl.write = mesh_write;
  mesh->meta.vtbl.free = mesh_free;
  mesh->meta.vtbl.size = mesh_size;
}

static void mesh_write(void* block, FILE* fp, uint64_t offset) {
  blk_mesh* mesh = (blk_mesh*) block;

  /* assume file is open */
  fseek(fp, offset, SEEK_SET);
  fwrite(&mesh->n_vertices, 1, fp);
  fwrite(mesh->vertices, mesh->n_vertices, 1, fp);
  fwrite(&mesh->n_normals, 1, fp);
  fwrite(mesh->normals, mesh->n_normals, 1, fp);
  fwrite(&mesh->n_texcoords, 1, fp);
  fwrite(mesh->texcoords, mesh->n_texcoords, 1, fp);
  fwrite(&mesh->n_colors, 1, fp);
  fwrite(mesh->colors, mesh->n_colors, 1, fp);
  fwrite(&mesh->n_indices, 1, fp);
  fwrite(mesh->indices, mesh->n_indices, 1, fp);
}

static void mesh_free(void* block) {
  blk_mesh* mesh = (blk_mesh*) block;

  free(mesh->vertices);
  free(mesh->normals);
  free(mesh->texcoords);
  free(mesh->colors);
  free(mesh->indices);
}

static uint64_t mesh_size(void* block) {
  const blk_mesh* mesh = (const blk_mesh*) block;

  return n_vertices * sizeof(float) +
         n_normals * sizeof(float) +
         n_texcoords * sizeof(float) +
         n_colors * sizeof(float)
         n_indices * sizeof(uint32_t) +
         sizeof(uint64_t) + /* n verts */
         sizeof(uint64_t) + /* n normals */
         sizeof(uint64_t) + /* n coords */
         sizeof(uint64_t) + /* n colors */
         sizeof(uint64_t) + /* n indices */
}
