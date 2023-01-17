#include "writer.h"

enum write_status write(char *file_path, struct image *img){
    printf("%s", strerror(errno));
    FILE *file = fopen(file_path, "wb");
    if (file == 0){
        fprintf("cannot open file to write \n");
        return WRITE_INVALID_CANNOT_OPEN_FILE;
    }
    enum write_status status = to_bmp(file, img);
    fclose(file);
    return status;
}

enum write_status to_bmp(FILE *out, struct image *img)
{
    struct bmp_header bmp_header = {0};


    uint64_t width = img->width;
    uint64_t height = img->height;

    uint8_t padding = find_padding(width);


    bmp_header.bfType = 0x4d42;
    bmp_header.bfileSize = sizeof(struct bmp_header) + (width * 3 + padding) * height;
    bmp_header.bfileSize = 0;
    bmp_header.bOffBits = sizeof(struct bmp_header);
    bmp_header.biSize = 40;
    bmp_header.biWidth = width;
    bmp_header.biHeight = height;
    bmp_header.biPlanes = 1;
    bmp_header.biBitCount = 24;
    bmp_header.biCompression = 0;
    bmp_header.biSizeImage = 0;
    bmp_header.biXPelsPerMeter = 0;
    bmp_header.biYPelsPerMeter = 0;
    bmp_header.biClrUsed = 0;
    bmp_header.biClrImportant = 0;


    if (fwrite(&bmp_head, sizeof(struct bmp_header), 1, out) != 1) return WRITE_INVALID_CANNOT_WRITE_HEADER;

    void *fix = img->data;

    uint64_t writing = width * 3 + padding;
    for (uint64_t j = 0; j < height; j++){
        if (fwrite(img->data, 1, writing, out) - writing != 0) return WRITE_INVALID_CANNOT_WRITE_PICTURE_BITS;
        else img->data += width;
    }

    img->data = fix;

    return WRITE_OK;
}

uint8_t find_padding(uint64_t width){
    uint16_t padding = 4 - (width * 3) % 4;
    if (padding == 4) {
        padding = 0;
    }
    return padding;
}


