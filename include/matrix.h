
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    float **entries;
    int row, col;
} matrix;

matrix *matrix_new(int row, int col);
void    matrix_free(matrix *m);
matrix *matrix_copy(matrix *m);

matrix *matrix_flatten(matrix *m);
void    matrix_transpose(matrix *m);
matrix *matrix_transpose_new(matrix *m);

void    matrix_write(matrix *m, FILE *f);
void    matrix_save(matrix *m, char *file_name);
matrix *matrix_read(FILE *f);
matrix *matrix_load(char *file_name);

matrix *matrix_dot(matrix *m, matrix *n);
matrix *matrix_multiply(matrix *m, matrix *n);

void    matrix_add(matrix *m, matrix *n);
matrix *matrix_add_new(matrix *m, matrix *n);

void    matrix_subtract(matrix *m, matrix *n);
matrix *matrix_subtract_new(matrix *m, matrix *n);

void    matrix_scale(matrix *m, float s);
matrix *matrix_scale_new(matrix *m, float s);

void    matrix_add_scalar(matrix *m, float s);
matrix *matrix_add_scalar_new(matrix *m, float s);

void    matrix_randomize(matrix *m);
void    matrix_fill(matrix *m, float s);

float   sigmoid(float x);
matrix *matrix_sigmoid(matrix *m);
matrix *matrix_sigmoid_prime(matrix *m);

matrix *matrix_softmax(matrix *m);

matrix *matrix_onehot_encode(int label);
int     matrix_onehot_decode(matrix *label);

#endif // MATRIX_H
