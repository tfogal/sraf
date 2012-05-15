#ifndef SCENE_IMAGE_H
#define SCENE_IMAGE_H

#include <inttypes.h>
#include "s-block.h"

typedef struct _image_block {
  block meta;
  void* data;
  uint64_t nx, ny;
  float x,y,z;
} blk_image;

blk_image* alloc_image_block();

#endif /* SCENE_IMAGE_H */
