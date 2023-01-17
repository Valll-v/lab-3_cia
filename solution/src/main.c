#include "read/reader.h"
#include "write/writer.h"

#include <stdio.h>

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning

    struct image img = {0};

    enum read_status rd_status = read(argv[1], &img);

    if (rd_status == READ_INVALID_BITS){
        printf("Битые пиксели в файле");
        return 1;
    }
    else if (rd_status == READ_INVALID_CANNOT_OPEN_FILE){
        printf("Файл для чтения невозможно открыть");
        return 1;
    }
    else if (rd_status == READ_INVALID_HEADER){
        printf("Неправильный заголовок в файле для чтения");
        return 1;
    }
    else if (rd_status == CREATE_INVALID_MEMORY_PROBLEMS){
        printf("Проблемы с памятью на устройстве, невозможно сохранить кратинку в память");
        return 1;
    }
    else{
        printf("Картинка с файла прочтена");
    }

    if (rotate(&img)){
        clear_image(&img);
        return 1;
    }
    else{
        printf("Картинка перевернута");
    }

    enum write_status wrt_status = write(argv[2], &img);

    if (wrt_status == WRITE_INVALID_CANNOT_OPEN_FILE){
        printf("Файл для записи невозможно открыть");
        return 1;
    }
    else if (wrt_status == WRITE_INVALID_CANNOT_WRITE_HEADER){
        printf("Невозможно написать заголовок файла");
        return 1;
    }
    else if (wrt_status == WRITE_INVALID_CANNOT_WRITE_PICTURE_BITS){
        printf("Невозможно записать пиксели в файл");
        return 1;
    }
    else {
        printf("Картинка записана в файл");
    }


    clear_image(&img);

    return 0;
}
