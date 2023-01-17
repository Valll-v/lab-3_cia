#include "reader.h"

uint8_t find_padding(uint64_t width){
    uint16_t padding = 4 - (width * 3) % 4;
    if (padding == 4) {
        padding = 0;
    }
    return padding;
}

enum read_status read(char *file_path, struct image *img){
    FILE *file = fopen(file_path, "rb");
    if (file == 0){
        printf("%s", strerror(errno));
        return READ_INVALID_CANNOT_OPEN_FILE;
    }
    enum read_status status  = from_bmp(file, img);
    fclose(file);
    return status;
}

enum read_status from_bmp(FILE *in, struct image *img)
{
    uint64_t width;
    uint64_t height;

    struct bmp_header bmp_head;
    if (fread(&bmp_head, sizeof(struct bmp_header), 1, in) != 1) return 1;

    width = bmp_head.biWidth;
    height = bmp_head.biHeight;

    if (bmp_head.bfType != 0x4d42) return READ_INVALID_HEADER;
    if (bmp_head.biBitCount != 24) return READ_INVALID_HEADER;
    if (bmp_head.biPlanes != 1) return READ_INVALID_HEADER;
    if (bmp_head.biCompression != 0) return READ_INVALID_HEADER;
    if (fseek(in, bmp_head.bOffBits, SEEK_SET) != 0) return READ_INVALID_HEADER;
    
    
    if (create_image(img, width, height)){
        return CREATE_INVALID_MEMORY_PROBLEMS;
    }    

    uint8_t padding = find_padding(img->width);

    struct pixel *data = img->data;
    uint32_t reading = img->width * 3 + padding;

    for (uint32_t i = 0; i < img->height; i++){
        if (fread(data, 1, reading, in) - reading != 0){
            return READ_INVALID_BITS;
        }
        else data += img->width;
    }

    return READ_OK;
}
