#ifndef PAIRS_H
#define PAIRS_H

#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>

struct pair
{
    int point1;
    int point2;
};
typedef struct pair pair_t;

struct pairs
{
    int size;
    pair_t *arr;
};
typedef struct pairs pairs_t;


rc_t pairs_read(pairs_t &pairs, FILE *f);
void pairs_free(const pairs_t &pairs);

#endif // PAIRS_H
