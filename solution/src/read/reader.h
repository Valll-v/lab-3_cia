#ifndef READER_H
#define READER_H

#include "../utils/image.h"
#include "../utils/bmh_header.h"

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>



enum read_status  {
  READ_OK = 0,
  READ_INVALID_CANNOT_OPEN_FILE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  CREATE_INVALID_MEMORY_PROBLEMS
  /* коды других ошибок  */
  };

enum read_status read(char *file_path, struct image *img);

enum read_status from_bmp( FILE* in, struct image* img);

uint8_t find_padding(uint64_t width);



#endif
