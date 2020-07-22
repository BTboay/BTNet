#ifndef CONVOLUTIONAL_LAYER_H
#define CONVOLUTIONAL_LAYER_H

#include "btnet.h"
#include "parser.h"

typedef layer convolutional_layer;

convolutional_layer create_convolutional_layer(LayerParams *p);
#endif