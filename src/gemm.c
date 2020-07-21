#include "gemm.h"

int find_index(int i, int j, int k, int size, int stride, int h, int w, int out_h, int out_w)
{
    int index_h = j / size + (k / out_w)*size;
    int index_w = j % size + (k % out_w)*size;
    int index = (i*h + index_h)*w + index_w;
    return index;
}

int *average_gemm(float *data, int c, int num, int m, int size, int stride, int h, int w, int out_h, int out_w, float *workspace)
{
    int i,j,k;
    int *index = malloc(m*c*size*size*sizeof(int));
    float scale = (float)1/num;
    #pragma omp parallel for
    for (i = 0; i < c; ++i){
        for (j = 0; j < num; ++j){
            for (k = 0; k < m; ++k){
                workspace[i*m+k] += scale * data[i*num*m+j*m+k];
                index[i*num*m+j*m+k] = find_index(i, j, k, size, stride, h, w, out_h, out_w);
            }
        }
    }
    return index;
}

int *max_gemm(float *data, int c, int num, int m, int size, int stride, int h, int w, int out_h, int out_w, float *workspace)
{
    int i,j,k;
    int *index = malloc(c*m*sizeof(int));
    #pragma omp parallel for
    for (i = 0; i < c; ++i){
        for (j = 0; j < num; ++j){
            for (k = 0; k < m; ++k){
                if (workspace[i*m+k] < data[i*num*m+j*m+k]){
                    workspace[i*m+k] = data[i*num*m+j*m+k];
                    index[i*m+k] = find_index(i, j, k, size, stride, h, w, out_h, out_w);
                }
            }
        }
    }
    return index;
}

void gemm(float *data, float *weights, int n, int num, int m, float *output)
{
    int i, j, k;
    for (i = 0; i < n; ++i){
        for (j = 0; j < num; ++j){
            register float weight = weights[i*num+j];
            for (k = 0; k < m; ++k){
                output[i*m+k] += weight * data[j*m+k];
            }
        }
    }
}