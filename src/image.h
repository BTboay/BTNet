#ifndef IMAGE_H
#define IMAGE_H

typedef struct image
{
    int h;
    int w;
    int c;
    float *data;
} image;

image *load_image_data(char *img_path);
void save_image_data(image *img, char *savepath);
#endif