
#ifndef DATA_H
#define DATA_H

#include "matrix.h"
#include "common.h"

#define NETWORK_FILE "network.txt"

// I do not recommend loading all 30,000 samples of the training data.
// This program will load the entire 30,000 matrices of 728 floats into memory, if you tell it to.

// #define N_TRAIN_SAMPLES 30000
// #define N_TEST_SAMPLES 10000

#define N_TRAIN_SAMPLES 10000
#define N_TEST_SAMPLES 500

#define TRAIN_FILE "mnist_data/mnist_train.txt"
#define TEST_FILE "mnist_data/mnist_test.txt"

#define SAMPLE_WIDTH 28
#define SAMPLE_HEIGHT 28
#define N_LABELS 10
#define DATA_MAX 255

typedef struct {
    matrix *data;
    int label;
} sample;

sample *allocate_samples(int n_samples, char *file_name);
void    free_samples(int n_samples, sample *s);
sample *load_train();
sample *load_test();

#endif // DATA_H
