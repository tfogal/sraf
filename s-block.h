#ifndef SCENE_BLOCK_H
#define SCENE_BLOCK_H

#include <inttypes.h>
struct FILE;

typedef void (bfunc_write)(void* block, FILE*, uint64_t offset);
typedef void (bfunc_free)(void* block);
typedef uint64_t (bfunc_size)(void* block);

typedef struct _block_vtbl {
  bfunc_write* write;
  bfunc_free* free;
  bfunc_size* size;
} block_vtbl;

typedef struct _block {
  block_vtbl vtbl;
  uint64_t offset;
  struct _block* next;
} block;

#endif /* SCENE_BLOCK_H */
