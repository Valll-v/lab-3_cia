#ifndef IMAGE_H
#define IMAGE_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../read/reader.h"


struct image {
  uint64_t width, height;
  struct pixel* data;
};

struct pixel { 
    uint8_t b, g, r; 
};

int create_image(struct image* img, uint64_t width, uint64_t height);

struct pixel get_pixel(struct image* img, uint64_t width, uint64_t height);

void set_pixel(struct image* img, uint64_t width, uint64_t height, struct pixel pixel);

void clear_image(struct image* img);



#endif
