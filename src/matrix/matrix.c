
#ifndef MATRIX_C
#define MATRIX_C

#include "matrix.h"
#include "../data/data.h"
#include "../common.h"

matrix *matrix_new(int row, int col)
{
    matrix *new = malloc(sizeof(matrix));

    float **entries = malloc(sizeof(float *) * row);

    for (int i = 0; i < row; i++)
        entries[i] = malloc(sizeof(float) * col);


    new->row = row;
    new->col = col;
    new->entries = entries;

    matrix_fill(new, 0);

    return new;
}
void matrix_free(matrix *m)
{
    if (!m) return;

    for (int i = 0; i < m->row; i++)
        free(m->entries[i]);

    free(m->entries);
    free(m);
}
matrix *matrix_copy(matrix *m)
{
    if (!m) return NULL;

    matrix *copy = matrix_new(m->row, m->col);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            copy->entries[i][j] = m->entries[i][j];

    return copy;
}

matrix *matrix_flatten(matrix *m)
{
    if (!m) return NULL;

    int n_entries = m->row * m->col;

    matrix *flat = matrix_new(1, n_entries);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            flat->entries[0][i * m->col + j] = m->entries[i][j];

    return flat;
}
void matrix_transpose(matrix *m)
{
    matrix *transpose = matrix_transpose_new(m);
    matrix_free(m);
    m = transpose;
}
matrix *matrix_transpose_new(matrix *m)
{
    if (!m) return NULL;

    matrix *transpose = matrix_new(m->col, m->row);

    for (int i = 0; i < m->col; i++)
        for (int j = 0; j < m->row; j++)
            transpose->entries[i][j] = m->entries[j][i];

    return transpose;
}

void matrix_write(matrix *m, FILE *f)
{
    fprintf(f, "%d %d\n", m->row, m->col);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            fprintf(f, "%f%s", m->entries[i][j], (j == m->col - 1 ? "\n" : " "));
}
void matrix_save(matrix *m, char *file_name)
{
    if (!m) return;

    FILE *f = fopen(file_name, "w");
    matrix_write(m, f);

    fclose(f);
}
matrix *matrix_read(FILE *f)
{
    int row, col;
    fscanf(f, "%d %d", &row, &col);

    matrix *m = matrix_new(row, col);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            fscanf(f, "%f", &m->entries[i][j]);

    return m;
}
matrix *matrix_load(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    matrix *m = matrix_read(f);
    fclose(f);

    return m;
}

matrix *matrix_dot(matrix *m, matrix *n)
{
    if (!m || !n) return NULL;

    CHECK_DIMS(m->col, n->row);

    matrix *prod = matrix_new(m->row, n->col);

    for (int i = 0; i < prod->row; i++)
        for (int j = 0; j < prod->col; j++)
            for (int k = 0; k < m->col; k++)
                prod->entries[i][j] += m->entries[i][k] * n->entries[k][j];

    return prod;
}
matrix *matrix_multiply(matrix *m , matrix *n)
{
    if (!m || !n)
        return NULL;

    CHECK_DIMS(m->row, n->row);
    CHECK_DIMS(m->col, n->col);

    matrix *prod = matrix_new(m->row, m->col);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            prod->entries[i][j] = m->entries[i][j] * n->entries[i][j];

    return prod;
}

void matrix_add(matrix *m, matrix *n)
{
    if (!m || !n)
        return;

    CHECK_DIMS(m->row, n->row);
    CHECK_DIMS(m->col, n->col);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] += n->entries[i][j];
}
matrix *matrix_add_new(matrix *m, matrix *n)
{
    if (!m || !n)
        return NULL;

    CHECK_DIMS(m->row, n->row);
    CHECK_DIMS(m->col, n->col);

    matrix *sum = matrix_copy(m);
    matrix_add(sum, n);

    return sum;
}

void matrix_subtract(matrix *m, matrix *n)
{
    if (!m || !n)
        return;

    CHECK_DIMS(m->row, n->row);
    CHECK_DIMS(m->col, n->col);

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] -= n->entries[i][j];
}
matrix *matrix_subtract_new(matrix *m, matrix *n)
{
    if (!m || !n)
        return NULL;

    CHECK_DIMS(m->row, n->row);
    CHECK_DIMS(m->col, n->col);

    matrix *diff = matrix_copy(m);
    matrix_subtract(diff, n);

    return diff;
}

void matrix_scale(matrix *m, float s)
{
    if (!m)
        return;

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] *= s;
}
matrix *matrix_scale_new(matrix *m, float s)
{
    if (!m)
        return NULL;

    matrix *result = matrix_copy(m);
    matrix_scale(result, s);

    return result;
}

void matrix_add_scalar(matrix *m, float s)
{
    if (!m)
        return;

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] += s;
}
matrix *matrix_add_scalar_new(matrix *m, float s)
{
    if (!m)
        return NULL;
    
    matrix *result = matrix_copy(m);
    matrix_add_scalar(result, s);

    return result;
}

void matrix_randomize(matrix *m)
{
    srand(time(0));

    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] = (float) rand() / (float) (RAND_MAX);
}
void matrix_fill(matrix *m, float s)
{
    for (int i = 0; i < m->row; i++)
        for (int j = 0; j < m->col; j++)
            m->entries[i][j] = s;
}

float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}
matrix *matrix_sigmoid(matrix *m)
{
    matrix *result = matrix_copy(m);

    for (int i = 0; i < result->row; i++)
        for (int j = 0; j < result->col; j++)
            result->entries[i][j] = sigmoid(result->entries[i][j]);

    return result;
}
matrix *matrix_sigmoid_prime(matrix *m)
{
    matrix *n = matrix_sigmoid(m);

    matrix *ones = matrix_copy(n);
    matrix_fill(ones, 1);

    matrix *one_minus_n = matrix_subtract_new(ones, n);
    matrix *result = matrix_multiply(n, one_minus_n);

    matrix_free(n);
    matrix_free(ones);
    matrix_free(one_minus_n);

    return result;
}

matrix *matrix_softmax(matrix *m)
{
    CHECK_DIMS(m->col, 1);

    float sum = 0;
    for (int i = 0; i < m->row; i++) {
        sum += exp(m->entries[i][0]);
    }
    
    matrix *result = matrix_new(m->row, 1);

    for (int i = 0; i < m->row; i++)
        result->entries[i][0] = exp(m->entries[i][0]) / sum;

    return result;
}

matrix *matrix_onehot_encode(int label)
{
    matrix *encoded = matrix_new(N_LABELS, 1);
    encoded->entries[label][0] = 1;
    return encoded;
}
int matrix_onehot_decode(matrix *label)
{
    int max = 0;

    for (int i = 0; i < label->row; i++)
        if (label->entries[i][0] > label->entries[max][0])
            max = i;

    return max;
}

#endif // MATRIX_C
