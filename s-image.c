#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "s-image.h"

static void img_write(void* block, FILE* fp, uint64_t offset) {
  blk_image* img = (blk_image*)block;

  /* assume the file is already open. */
  fseek(fp, offset, SEEK_SET);
  fwrite(&img->nx, sizeof(uint64_t), 1, fp);
  fwrite(&img->ny, sizeof(uint64_t), 1, fp);
  fwrite(&img->x, sizeof(float), 1, fp);
  fwrite(&img->y, sizeof(float), 1, fp);
  fwrite(&img->z, sizeof(float), 1, fp);
  fwrite(img->data, img->nx*img->ny*4, 1, fp);
}

static void img_free(void* _sraf) {
  blk_image* img = (blk_image*)block;
  free(img->data);
}

blk_image* alloc_image_block() {
  blk_image* b = calloc(sizeof(blk_image), 1);
  b->meta.vtbl.write = img_write;
  b->meta.vtbl.free = img_free;
  b->meta.vtbl.size = NULL; /* fixme */
  return b;
}
