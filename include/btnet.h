#ifndef BTNET
#define BTNET

#include "gemm.h"
#include "im2col.h"
#include "utils.h"
#include "image.h"
#include "pooling.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum pooling_type{
    AVERAGE, MAX
} pooling_type;

typedef enum layer_type{
    CONVOLUTIONAL, POOLING, FULLCONNECT
} layer_type;

typedef enum activation{
    TANH
} activation;

typedef struct layer
{
    layer_type type_layer;
    pooling_type type_pool;
    int filters;
    int size;
    int stride;
    int pad;
    activation activate;
} layer;
#endif