
#include "network.h"

#ifndef NETWORK_C
#define NETWORK_C

network *network_new(int in, int hid, int out, float lr)
{
    network *new = malloc(sizeof(network));

    new->input  = in;
    new->hidden = hid;
    new->output = out;

    new->learning_rate = lr;

    new->hidden_weights = matrix_new(hid, in);
    new->output_weights = matrix_new(out, hid);

    matrix_randomize(new->hidden_weights);
    matrix_randomize(new->output_weights);

    return new;
}
void network_free(network *n)
{
    matrix_free(n->hidden_weights);
    matrix_free(n->output_weights);
    free(n);
}

matrix *network_predict(network *n, matrix *input)
{
    matrix *hidden_values = matrix_dot(n->hidden_weights, input);
    matrix *hidden_output = matrix_sigmoid(hidden_values);

    matrix *final_values = matrix_dot(n->output_weights, hidden_output);
    matrix *final_output = matrix_sigmoid(final_values);

    matrix *result = matrix_softmax(final_output);

    matrix_free(hidden_values);
    matrix_free(hidden_output);
    matrix_free(final_values);
    matrix_free(final_output);

    return result;
}
void backprop(matrix *weights, matrix *error, matrix *inputs, matrix *outputs, float lr) 
{
    // backpropagate
    //  weights += lr * (((error * s'(outputs)) @ inputs^T),

    matrix *scaled, *dotted, *multiplied, *sig_prime, *inputs_t;

    matrix_add(
        weights,
        scaled = matrix_scale_new(
            dotted = matrix_dot(
                multiplied = matrix_multiply(
                    error,
                    sig_prime = matrix_sigmoid_prime(outputs)
                ),
                inputs_t = matrix_transpose_new(inputs)
            ),
            lr
        )
    );

    matrix_free(scaled);
    matrix_free(dotted);
    matrix_free(multiplied);
    matrix_free(sig_prime);
    matrix_free(inputs_t);
}
void network_update(network *n, sample *s)
{
    matrix *input = s->data;
    matrix *output = matrix_onehot_encode(s->label);

    // Feedforward
    matrix *hidden_values = matrix_dot(n->hidden_weights, input);
    matrix *hidden_output = matrix_sigmoid(hidden_values);
    matrix *final_values = matrix_dot(n->output_weights, hidden_output);
    matrix *final_output = matrix_sigmoid(final_values);

    // Calculate error
    matrix *output_error = matrix_subtract_new(output, final_output);
    matrix *output_weights_t = matrix_transpose_new(n->output_weights);
    matrix *hidden_error = matrix_dot(output_weights_t, output_error);

    backprop(
        n->output_weights,
        output_error,
        hidden_output,
        final_output,
        n->learning_rate
    );

    backprop(
        n->hidden_weights,
        hidden_error,
        input,
        hidden_output,
        n->learning_rate
    );

    matrix_free(output);
    matrix_free(hidden_values);
    matrix_free(hidden_output);
    matrix_free(final_values);
    matrix_free(final_output);
    matrix_free(output_error);
    matrix_free(output_weights_t);
    matrix_free(hidden_error);
}

void network_train(network *n, sample *training_set)
{
    float percent_complete = 0.0;

    for (int i = 0; i < N_TRAIN_SAMPLES; i++) {
        percent_complete = i / (float) N_TRAIN_SAMPLES * 100;

        fprintf(stderr, "Training... %.2f%% complete.\r", percent_complete);
        network_update(n, training_set + i);
    }
    fprintf(stderr, "\nDone!\nSaving to %s\n", NETWORK_FILE);
    
    network_save(n, NETWORK_FILE);
}
float network_test(network *n, sample *test_set)
{
    int correct = 0;
    float percent_complete = 0.0;

    for (int i = 0; i < N_TEST_SAMPLES; i++)
    {
        percent_complete = i / (float) N_TEST_SAMPLES * 100;

        sample *s = test_set + i;
        matrix *data = s->data;
        int label = s->label;

        matrix *prediction = network_predict(n, data);
        int pred = matrix_onehot_decode(prediction);
        matrix_free(prediction);
        
        correct += (pred == label);
    }

    fprintf(stderr, "\nDone!\n");
    fprintf(stderr, "\nAccuracy: %.2f%%\n", (float) correct / N_TEST_SAMPLES * 100);

    return (float) correct / N_TEST_SAMPLES * 100;
}

void network_write(network *n, FILE *f)
{
    fprintf(f, "%d %d %d %f\n", n->input, n->hidden, n->output, n->learning_rate);
    matrix_write(n->hidden_weights, f);
    matrix_write(n->output_weights, f);
}
void network_save(network *n, char *file_name)
{
    FILE *f = fopen(file_name, "w");
    network_write(n, f);
    fclose(f);
}
network *network_load(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    int in, hid, out;
    float lr;

    fscanf(f, "%d %d %d %f", &in, &hid, &out, &lr);

    network *n = network_new(in, hid, out, lr);
    matrix_free(n->hidden_weights);
    matrix_free(n->output_weights);

    n->hidden_weights = matrix_read(f);
    n->output_weights = matrix_read(f);

    fclose(f);
    return n;
}

#endif // NETWORK_C
