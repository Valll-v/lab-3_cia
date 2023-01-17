#include "rotater.h"

int rotate(struct image *img){

    struct image new;

    uint32_t width = img->height;
    uint32_t height = img->width;

    if(create_image(&new, width, height)){
        return 1;
    }

    for(int i = 0; i < img->width; i++){
        for(int j = 0; j < img->height; j++){
            set_pixel(&new, (img->height - j - 1), i , get_pixel(img, i, j));
        }
    }

    clear_image(img);
    *img = new;

    return 0;

}
