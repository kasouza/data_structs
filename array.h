#ifndef KASOUZA_HOME_KASO_PROJECTS_PERSONAL_DATA_STRUCTS_ARRAY_H
#define KASOUZA_HOME_KASO_PROJECTS_PERSONAL_DATA_STRUCTS_ARRAY_H

#include <stddef.h>

#define ARRAY_INITIAL_SIZE 2

typedef struct {
    size_t capacity;
    size_t length;
} ArrayHeader;

#define array_init(T) (_array_init(sizeof(T)))

#define array_length(array) (_array_length(array, sizeof(*array)))

#define array_push(array, item)                                                \
    do {                                                                       \
        array = _array_grow(array, 1, sizeof(*array));                         \
        array[array_length(array) - 1] = item;                                 \
    } while (0)

#define array_remove(array, idx)                                               \
    do {                                                                       \
        array[idx] = array[array_length(array) - 1];                           \
        _array_shrink(array, 1, sizeof(*array));                               \
    } while (0)

#define array_pop(array) array_remove(array, array_length(array) - 1)

void *_array_init(size_t item_size);
size_t _array_length(void *array, size_t item_size);
void _array_remove(void *array, size_t idx, size_t item_size);

// Does not resize the array, just change the legnth
void _array_shrink(void *array, size_t shrink_by, size_t item_size);
void *_array_grow(void *array, size_t grow_by, size_t item_size);

#endif
