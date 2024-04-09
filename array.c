#include "array.h"

#include <assert.h>
#include <malloc.h>
#include <stddef.h>

size_t get_padding(size_t item_size) {
    size_t header_size = sizeof(ArrayHeader);
    size_t padding = item_size > header_size ? item_size - header_size
                                             : header_size - item_size;
    return padding;
}

ArrayHeader *get_header(void *array, size_t item_size) {
    size_t header_size = sizeof(ArrayHeader);
    size_t padding = get_padding(item_size);

    char *header_bytes = ((char *)array) - header_size - padding;
    ArrayHeader *header = ((ArrayHeader *)header_bytes);

    return header;
}

void *_array_init(size_t item_size) {
    void *items = NULL;

    size_t header_size = sizeof(ArrayHeader);
    size_t array_size = item_size * ARRAY_INITIAL_SIZE;
    size_t padding = item_size > header_size ? item_size - header_size
                                             : header_size - item_size;

    ArrayHeader *header = malloc(header_size + padding + array_size);

    if (header) {
        header->capacity = ARRAY_INITIAL_SIZE;
        header->length = 0;
        items = ((char *)header) + header_size + padding;
    }

    return items;
}

size_t _array_length(void *array, size_t item_size) {
    ArrayHeader *header = get_header(array, item_size);
    return header->length;
}

void *_array_grow(void *array, size_t grow_by, size_t item_size) {
    ArrayHeader *header = get_header(array, item_size);

    if (header->length + grow_by > header->capacity) {
        size_t new_capacity = header->capacity * 2;
        size_t header_size = sizeof(ArrayHeader);
        size_t padding = get_padding(item_size);
        size_t array_size = item_size * new_capacity;

        header = realloc(header, header_size + padding + array_size);
        header->capacity = new_capacity;

        array = ((char *)header) + header_size + padding;
    }

    header->length += grow_by;

    return array;
}

void _array_shrink(void *array, size_t shrink_by, size_t item_size) {
    ArrayHeader *header = get_header(array, item_size);

    assert(header->length - shrink_by >= 0);
    header->length -= shrink_by;
}
