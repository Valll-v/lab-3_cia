#ifndef WRITER_H
#define WRITER_H

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "../utils/bmh_header.h"


/*  serializer   */
enum  write_status  {
  WRITE_OK = 0,
  WRITE_INVALID_CANNOT_WRITE_HEADER,
  WRITE_INVALID_CANNOT_OPEN_FILE,
  WRITE_INVALID_CANNOT_WRITE_PICTURE_BITS
  /* коды других ошибок  */
};

enum write_status write(char *file_path, struct image *img);

enum write_status to_bmp( FILE* out, struct image* img);

uint8_t find_padding(uint64_t width);


#endif
