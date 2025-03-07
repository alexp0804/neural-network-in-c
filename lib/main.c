#include "../include/common.h"
#include "matrix.c"
#include "data.c"
#include "network.c"

int main(int argc, char **argv)
{
    network *net;

    int in  = SAMPLE_WIDTH * SAMPLE_WIDTH,
        hid = 300,
        out = N_LABELS;

    float lr = 0.01;

    // If a file with the given name exists, load from that instead
    if (access(NETWORK_FILE, F_OK) == 0)
        net = network_load(NETWORK_FILE);
    else
        net = network_new(in, hid, out, lr);

    // Must run with "train" or "test"
    if (argc != 2)
    {
        fprintf(stderr, "Usage: <test / train>\n");
        exit(EXIT_FAILURE);
    }

    // Train network
    if (strcmp(argv[1], "train") == 0)
    {
        sample *training_set = load_train();
        network_train(net, training_set);
        free_samples(N_TRAIN_SAMPLES, training_set);
    }
    // Test network
    else if (strcmp(argv[1], "test") == 0)
    {
        sample *test_set = load_test();
        network_test(net, test_set);
        free_samples(N_TEST_SAMPLES, test_set);
    }
    else
    {
        fprintf(stderr, "Usage: <test / train>\n");
    }

    network_free(net);

    return 0;
}
