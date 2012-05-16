#include <stdlib.h>
#include "sraf.h"

int main() {
  struct sraf* sra = sc_allocate("dummy.sraf");

  /* make an image with 4 squares: red, green, blue, r+g */
  const uint64_t nx = 64;
  const uint64_t ny = 64;
  uint8_t* data = malloc(nx * ny * sizeof(uint8_t) * 4);
  for(size_t y=0; y < ny; ++y) {
    for(size_t x=0; x < nx; ++x) {
      if(x < 32 && y < 32) {
        data[y*(nx*4) + x*4 + 0] = 255;
        data[y*(nx*4) + x*4 + 1] = 0;
        data[y*(nx*4) + x*4 + 2] = 0;
      } else if(x >= 32 && y < 32) {
        data[y*(nx*4) + x*4 + 0] = 0;
        data[y*(nx*4) + x*4 + 1] = 128;
        data[y*(nx*4) + x*4 + 2] = 0;
      } else if(x < 32 && y >= 32) {
        data[y*(nx*4) + x*4 + 0] = 0;
        data[y*(nx*4) + x*4 + 1] = 0;
        data[y*(nx*4) + x*4 + 2] = 192;
      } else {
        data[y*(nx*4) + x*4 + 0] = 64;
        data[y*(nx*4) + x*4 + 1] = 64;
        data[y*(nx*4) + x*4 + 2] = 0;
      }
      data[y*(nx*4) + x*4 + 3] = 255;
    }
  }

  sc_add_image(sra, data, nx,ny, 0.0f,0.0f,0.0f);

  sc_free(sra);

  return 0;
}
