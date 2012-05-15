#ifndef SCENE_SRAF_H
#define SCENE_SRAF_H

#include <inttypes.h>

struct sraf;

struct sraf* sc_allocate();
/** free an SRA file.  No guarantee that it exists on disk until you call this.
 */
void sc_free(struct sraf*);

/** adds an RGBA image to an SRA file.
 * @param data: the actual data.  The library 'owns' it at this point.
 * @param nx: number of pixels in the image in X
 * @param x, y, z: lower left corner of the image in world space */
void sc_add_image(struct sraf*, void* data, size_t nx, size_t ny,
                  float x, float y, float z);
/** adds a mesh to an SRA file.  All elements must be triangles.
 * @param vertices vertex data
 * @param n_vertices number of vertices in the array */
void sc_add_mesh(struct sraf*,
                 float* vertices, size_t n_vertices,
                 float* normals, size_t n_normals,
                 float* texcoords, size_t n_texcoords,
                 float* colors, size_t n_colors,
                 uint32_t* indices, size_t n_indices);

#endif /* SCENE_SRAF_H */
