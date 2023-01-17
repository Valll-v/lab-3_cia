#include "image.h"

int create_image(struct image *img,  uint64_t width, uint64_t height){
    
    uint16_t len = width* height * (sizeof(struct pixel))+4;

    img->data = malloc(len);
    img->height = height;
    img->width = width;

    if (img->data == 0){
        return 1;
    }
    // for (uint16_t i = 0; i < len; i++){
    //     ((char*)img->data)[i] = 0;
    // }
    return 0;
}

void clear_image(struct image *img){
    free(img -> data);
}

void set_pixel(struct image *img, uint64_t width, uint64_t height, struct pixel pixel){
    img->data[width + img->width* height] = pixel;
}

struct pixel get_pixel(struct image *img,  uint64_t width, uint64_t height){
    return img->data[width + img->width * height];
}
