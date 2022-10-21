#include <stdio.h>
#include <string.h>
#include "str_ser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: ./a.out <str>");
        return 0;
    }
    struct buffer * buf = buffer_create();

    struct serializer * ser1 = serializer_create();
    ser1->out_buf = buf;

    char * tmp = argv[1];

    encode_str(ser1, tmp, strlen(tmp));
    // printf("out_buf index: %d", ser->out_buf->index);

    for (int i = 0 ; i < ser1->out_buf->index; i++) {
        printf("%x ", ser1->out_buf->data[i]);
    }
    printf("\n");


    struct serializer *ser2 = serializer_create();
    ser2->in_buf = buf;
    ser2->in_buf->index = 0;

    //int str_len = decode_str_length(ser2, 4);
    //printf("\n%d", str_len);

    char * content = decode_str_content(ser2);
    // printf("%d", ser2->in_buf->index);
    printf("%s\n", content);




}