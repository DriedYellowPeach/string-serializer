struct buffer {
    char * data;
    int index;
};

struct buffer * buffer_create();

void buffer_destroy(void * buf);
    

struct serializer {
    struct buffer * out_buf;
    struct buffer * in_buf;
};

struct serializer * serializer_create();

void serializer_destroy(void * ptr);

void encode_str(struct serializer* ser, char *str, int len);

char* decode_str(struct serializer *ser);

int decode_str_length(struct serializer *ser, int length_encoding_len);

char* decode_str_content(struct serializer *ser);




