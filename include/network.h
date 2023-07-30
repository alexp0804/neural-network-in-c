
#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include "data.h"

typedef struct {
    int input, hidden, output;
    float learning_rate;
    matrix *hidden_weights, *output_weights;
} network;

network *network_new(int in, int hid, int out, float lr);
void     network_free(network *n);

matrix  *network_predict(network *n, matrix *input);
void     network_backprop(matrix *weights, matrix *error, matrix *inputs, matrix *outputs, float lr);
void     network_update(network *n, sample *samples);

void     network_train(network *n, sample *training_set);
float    network_test(network *n, sample *test_set);

void     network_write(network *n, FILE *f);
void     network_save(network *n, char *file_name);
network *network_load(char *file_name);

#endif // NETWORK_H
