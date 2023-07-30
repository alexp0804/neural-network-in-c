
#ifndef DATA_C
#define DATA_C

#include "../include/data.h"

sample *allocate_samples(int n_samples, char *file_name) 
{
    sample *samples = malloc(sizeof(sample) * n_samples);

    for (int i = 0; i < n_samples; i++)
        samples[i].data = matrix_new(SAMPLE_WIDTH * SAMPLE_HEIGHT, 1);

    FILE *f = fopen(file_name, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Unable to load %s. Exitting.", file_name);
        free(samples);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n_samples; i++)
    {
        fscanf(f, "%d", &samples[i].label);

        for (int x = 0; x < SAMPLE_WIDTH; x++)
        {
            for (int y = 0; y < SAMPLE_HEIGHT; y++)
            {
                float *to_load = &samples[i].data->entries[y * SAMPLE_HEIGHT + x][0];
                fscanf(f, "%f", to_load);
                *to_load /= (float) DATA_MAX;
            }
        }
    }

    fclose(f);
    return samples;
}

void free_samples(int n_samples, sample *s)
{
    for (int i = 0; i < n_samples; i++) 
        matrix_free(s[i].data);
    
    free(s);
}

sample *load_train()
{
    fprintf(stderr, "Loading training data...");
    sample *training_data = allocate_samples(N_TRAIN_SAMPLES, TRAIN_FILE);
    fprintf(stderr, "\33[2K\rTraining data loaded!\n");
    return training_data;
}

sample *load_test()
{
    fprintf(stderr, "Loading testing data...");
    sample *testing_data = allocate_samples(N_TEST_SAMPLES, TEST_FILE);
    fprintf(stderr, "\33[2K\rTesting data loaded!\n");
    return testing_data;
}

#endif // DATA_C
