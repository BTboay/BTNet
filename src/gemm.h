#ifndef GEMM_H
#define GEMM_H

#include <stdio.h>
#include <stdlib.h>

int find_index(int i, int j, int k, int size, int stride, int h, int w, int out_h, int out_w);
int *average_gemm(float *data, int c, int num, int m, int size, int stride, int h, int w, int out_h, int out_w, float *workspace);
int *max_gemm(float *data, int c, int num, int m, int size, int stride, int h, int w, int out_h, int out_w, float *workspace);
void gemm(float *data, float *weights, int n, int num, int m, float *output);
#endif