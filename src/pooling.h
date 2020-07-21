#ifndef POOLING_H
#define POOLING_H

#include "im2col.h"
#include "gemm.h"
#include "utils.h"

typedef struct pooling_param
{
    float *data;
    int *index;
} pooling_param;


pooling_param *average_pool(float *im, int h, int w, int c, int size);
pooling_param *max_pool(float *im, int h, int w, int c, int size);
float *backward_max_pool(float *data, int *index, int inputs, int outputs);
float *backward_average_pool(float *data, int *index, int c, int num, int size, int inputs, int outputs);
#endif