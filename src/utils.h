#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void fill_cpu_float(float *data, float x, int num);
float *flid_float_cpu(float *data, int h, int w, int c);
char *fgetl(FILE *fp);
void strip(char *line);
#endif