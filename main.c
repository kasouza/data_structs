#include "array.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THICKNESS 5

typedef struct {
    long thick[THICKNESS];

    bool t;
    bool t2;
    bool t3;
    bool t4;
    bool t5;
    bool t6;
    bool t7;
    bool t8;

    /*bool b3;*/
    /*bool b4;*/
    /*bool b5;*/
    /*bool b6;*/
} ThickStruct;

ThickStruct make_thick_struct() {
    ThickStruct thick;
    for (size_t i = 0; i < THICKNESS; i++) {
        thick.thick[i] = random();
    }

    return thick;
}

typedef int *IntArray;

#define align_and_size(T)                                                      \
    printf("Align: %ld Size: %ld\n", _Alignof(T), sizeof(T))

int main() {
    srand(time(NULL));
    align_and_size(int);
    align_and_size(ThickStruct);

    IntArray nums = array_init(int);
    array_push(nums, 33);
    array_push(nums, 34);
    array_push(nums, 40);
    array_push(nums, 21);

    /*array_pop(nums);*/
    /*array_pop(nums);*/
    /*array_pop(nums);*/
    /*array_pop(nums);*/

    array_push(nums, 40);

    for (size_t i = 0; i < array_length(nums); i++) {
        printf("%d\n", nums[i]);
    }

    printf("\n\n");

    ThickStruct *thick = array_init(ThickStruct);
    array_push(thick, make_thick_struct());
    array_push(thick, make_thick_struct());
    array_push(thick, make_thick_struct());
    array_push(thick, make_thick_struct());

    for (size_t i = 0; i < array_length(thick); i++) {
        for (size_t j = 0; j < THICKNESS; j++) {
            printf("%ld", thick[i].thick[i]);
        }
    }

    return 0;
}
