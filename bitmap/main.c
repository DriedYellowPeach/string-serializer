#include <stdio.h>
typedef struct {
char* bits;
int size;
}bitvector;


bitvector* create_bitvec(int n_bits) {
    bitvector* vec = (bitvector*)malloc(sizeof(bitvector));
int size = sizeof(bitvector) * ceil(n_bits/8.0);
    vec->size = size;
    vec->bits = (char*)malloc(size);
return vec;
}
void destroy_bitvec(bitvector *vec) {
free(vec->bits);
free(vec);
}
void set_bit(bitvector* vec, int index, int bit) {
int byte = index >> 3;
int n = sizeof(index)*8-3;
int offset = ((unsigned) index << n) >> n;
if (bit) {
        vec->bits[byte] |= 1 << (7-offset);
    } else {
        vec->bits[byte] &= ~(1 << (7-offset));
    }
}
int get_bit(bitvector* vec, int index) {
int byte = index >> 3;
int n = sizeof(index)*8-3;
int offset = ((unsigned) index << n) >> n;
if (vec->bits[byte] & (1 << (7- offset))) {
return 1;
    } else {
return 0;
    }
}
int main(int argc, char *argv[])
{
int size = 1024;
int i = 0;
    bitvector *vec = create_bitvec(size);
for (i = 0; i < size; i++) {
if (i % 2 == 0) {
set_bit(vec, i, 0);
        } else {
set_bit(vec, i, 1);
        }
    }
for (i = 0; i < size; i++) {
printf("%d", get_bit(vec, i));
    }
destroy_bitvec(vec);
return 0;
}