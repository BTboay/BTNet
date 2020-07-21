#include "pooling.h"

pooling_param *max_pool(float *im, int h, int w, int c, int size)
{
    pooling_param *p = malloc(sizeof(pooling_param));
    int num = size*size;
    int h_out = (h - size) / size + 1;
    int w_out = (w - size) / size + 1;
    int c_out = c;
    int workspace_num = num * c * h_out * w_out;
    int result_num = h_out * w_out * c_out;
    float *workspace = malloc(workspace_num*sizeof(float));
    float *output = malloc(result_num*sizeof(float));
    im2col_cpu(im, h, w, c, size, size, 0, workspace);
    int *index = max_gemm(workspace, c, num, h_out*w_out, size, size, h, w, h_out, w_out, output);
    p->data = output;
    p->index = index;
    return p;
}


pooling_param *average_pool(float *im, int h, int w, int c, int size)
{
    pooling_param *p = malloc(sizeof(pooling_param));
    int num = size*size;
    int h_out = (h - size) / size + 1;
    int w_out = (w - size) / size + 1;
    int c_out = c;
    int workspace_num = num * c * h_out * w_out;
    int result_num = h_out * w_out * c_out;
    float *workspace = malloc(workspace_num*sizeof(float));
    float *output = malloc(result_num*sizeof(float));
    im2col_cpu(im, h, w, c, size, size, 0, workspace);
    int *index = average_gemm(workspace, c, num, h_out*w_out, size, size, h, w, h_out, w_out, output);
    p->data = output;
    p->index = index;
    return p;
}

float *backward_max_pool(float *data, int *index, int inputs, int outputs)
{
    int i;
    float *output = malloc(outputs*sizeof(float));
    fill_cpu_float(output, 0., outputs);
    for (i = 0; i < inputs; ++i){
        int key = index[i];
        output[key] = data[i];
    }
    for (i = 0; i < outputs; ++i){
        printf("%f\n", output[i]);
    }
    return output;
}

float *backward_average_pool(float *data, int *index, int c, int num, int size, int inputs, int outputs)
{
    int i, j, k;
    float *output = malloc(outputs*sizeof(float));
    fill_cpu_float(output, 0., outputs);
    for (i = 0; i < c; ++i){
        for (j = 0; j < num; ++j){
            float x = data[i*num+j];
            for (k = 0; k < size*size; ++k){
                int y = i*size*size*num + k*num + j;
                int key = index[y];
                output[key] = x;
            }
        }
    }
    return output;
}