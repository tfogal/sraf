#include <stdio.h>
#include <stdlib.h>
#include "sraf.h"
#include "s-block.h"
#include "s-image.h"

struct sra {
  FILE* f;
  block *blocks;
};

static const uint64_t header_size = 4;

static void add_block(struct sra* s, block* newblock) {
  uint64_t offset = 0;

  newblock->next = NULL;
  if(!s->blocks) { /* first block */
    newblock->offset = header_size;
    s->blocks = newblock;
    return;
  }

  struct _block* b = s->blocks;
  while(b && b->next) { offset += b->vtbl.size(b); b = b->next; }
  b->next = newblock;
  b->offset = offset;
}

/* blocks are dynamically allocated, must be dynamically freed. */
static void free_blocks(struct sra* s) {
  block* cur = s->blocks;
  while(cur) {
    block* prev = cur;
    cur = cur->next;
    prev->vtbl.free(prev);
    free(prev);
  }
}
static void write_header(struct sra* s) {
  const char* sraf = "SRAF";
  fwrite(sraf, 4, 1, s->f);
}

struct sraf* sc_allocate(const char* filename) {
  struct sra* s = calloc(1, sizeof(struct sra));
  s->f = fopen(filename, "w+b");
  return (struct sraf*) s;
}
void sc_free(struct sraf* sraf) {
  struct sra* s = (struct sra*) sraf;

  write_header(s);
  block *b = s->blocks;
  while(b) {
    b->vtbl.write(b, s->f, b->offset);
    b = b->next;
  }
  free_blocks(s);
  fclose(s->f);
  free(sraf);
}

/** adds an RGBA image to an SRA file.
 * @param nx: number of pixels in the image in X
 * @param x, y, z: lower left corner of the image in world space */
void sc_add_image(struct sraf* _sraf, void* data, uint64_t nx, uint64_t ny,
                  float x, float y, float z)
{
  struct sra* s = (struct sra*) _sraf;
  blk_image* img = alloc_image_block();
  img->data = data;
  img->nx = nx; img->ny = ny;
  img->x = x; img->y = y; img->z = z;
  add_block(s, (void*)img); /** @todo FIXME this is broken */
}

/** adds a mesh to an SRA file.  All elements must be triangles.
 * @param vertices vertex data
 * @param n_vertices number of vertices in the array */
void sc_add_mesh(struct sraf* _sraf,
                 float* vertices, uint64_t n_vertices,
                 float* normals, uint64_t n_normals,
                 float* texcoords, uint64_t n_texcoords,
                 float* colors, uint64_t n_colors,
                 uint32_t* indices, uint64_t n_indices)
{
  (void) _sraf;
  (void) vertices; (void) n_vertices;
  (void) normals; (void) n_normals;
  (void) texcoords; (void) n_texcoords;
  (void) colors; (void) n_colors;
  (void) indices; (void) n_indices;
}
