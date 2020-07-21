#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "image.h"

image *load_image_data(char *img_path)
{
    image *im_new = malloc(sizeof(image));
    int w, h, c;
    unsigned char *data = stbi_load(img_path, &w, &h, &c, 0);
    float *im_data = malloc((w*h*c)*sizeof(float));
    int i, j, k;
    for(k = 0; k < c; ++k){
        for(j = 0; j < h; ++j){
            for(i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                im_data[dst_index] = (float)data[src_index]/255.;
            }
        }
    }
    im_new->h = h;
    im_new->w = w;
    im_new->c = c;
    im_new->data = im_data;
    free(data);
    return im_new;
}

void save_image_data(image *img, char *savepath)
{
    int i, k;
    unsigned char *data = malloc(img->w*img->h*img->c*sizeof(char));
    for(k = 0; k < img->c; ++k){
        for(i = 0; i < img->w*img->h; ++i){
            data[i*img->c+k] = (unsigned char) (255*img->data[i + k*img->w*img->h]);
        }
    }
    stbi_write_png(savepath, img->w, img->h, img->c, data, img->w * img->c);
    free(data);
}