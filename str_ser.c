#include "str_ser.h"
#include <stdlib.h>
#include <stdio.h>


#define INTLEN 4
#define BUFF_SIZE 1024

struct buffer * buffer_create() {
    struct buffer * buf = malloc(sizeof(struct buffer));
    buf->data = malloc(BUFF_SIZE);

    return buf;
}

static void debug_bytes(char *ptr, int len) {
    for (int i = 0 ; i < len; i++) {
        printf("%x ", ptr[i]);
    }
    printf("\n");
}

void buffer_destroy(void * buf) {
    struct buffer * my_buf = buf;
    free(my_buf->data);
    free(my_buf);
}

struct serializer * serializer_create() {
    struct serializer * ser = malloc(sizeof(struct serializer));

    return ser;
}

void serializer_destory(void * ptr) {
    struct serializer * ser = ptr;
    free(ser);
}

static void encode_int(int length, char **out, int * out_len) {
    *out_len = INTLEN;
    *out = (char *)malloc(sizeof(char) * (*out_len));
    char * first = (char *)&length;
    for (int i = 0; i < *out_len; i++) {
        (*out)[i] = *first;
        //printf("%x, %x\n", *first, (*out)[i]);
        first++;
    } 
}

void encode_str(struct serializer* ser, char *str, int str_len) {
    char *length_encoding = NULL;
    int length_encoding_len = 0;

    encode_int(str_len, &length_encoding, &length_encoding_len);
    // write length
    for (int i = 0; i < length_encoding_len; i++) {
        ser->out_buf->data[ser->out_buf-> index] = length_encoding[i];
        // printf("%x", length_encoding[i]);
        ser->out_buf->index += 1;
    }
    // printf("fist: %x", ser->out_buf->data[0]);
    free(length_encoding);
    // printf("second: %x", ser->out_buf->data[0]);

    // write str
    for (int i = 0; i < str_len; i++) {
        ser->out_buf->data[ser->out_buf->index] = str[i];
        ser->out_buf->index += 1;
    }
    // printf("3: %x", ser->out_buf->data[0]);
}

static int bytes_to_int(char * bts, int bts_len) {
    int ret = 0;
    // debug_bytes(bts, bts_len);
    for (int i = 0; i < bts_len; i++) {

        // printf("%d\n", ret);
        ret += bts[i] * ( 1 << 8 * i);
    }

    return ret;
}

int decode_str_length(struct serializer * ser, int length_encoding_len) {
    int str_length = 0;
    
    str_length = bytes_to_int(ser->in_buf->data + ser->in_buf->index, length_encoding_len);
    ser->in_buf->index += length_encoding_len;

    // printf("%d\n", ser->in_buf->index);
    return str_length;
}

char * decode_str_content(struct serializer *ser) {
    char * ret;
    int ret_len  = decode_str_length(ser, INTLEN);
    ret = malloc(sizeof(char) * ret_len + 1);

    for (int i = 0 ; i < ret_len ; i++) {
        ret[i] = ser->in_buf->data[ser->in_buf->index + i];
    }

    // printf("%d\n", ser->in_buf->index);
    // printf("%d\n", ret_len);
    ser->in_buf->index += ret_len;
    // printf("%d\n", ser->in_buf->index);
    ret[ret_len] = '\0';
    return ret;
}

