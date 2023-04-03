# neural-network-in-c
A neural network created from scratch, in C, to classify the MNIST dataset.

I created this using my own matrix library and implementation of a neural network, using gradient descent as the optimizer.

The network structure only supports a single hidden layer, as my main goal was to classify the MNIST dataset with decent accuracy.

The network supports:
 * an arbitrarily sized input layer
 * an arbitrarily sized hidden layer activated with the sigmoid function
 * an arbitrarily sized output layer activated with the sigmoid function

I trained the network on $60,000$ samples from the MNIST dataset with a network of $28^2$ input size and $300$ hidden nodes. 
With this training, I am able to achieve anywhere from 88% - 93% accuracy! This is pretty good considering there is no convolution or deep learning going on.

![Screenshot 2023-04-03 023841](https://user-images.githubusercontent.com/68084954/229430466-c7233e0d-a654-4c69-aee9-615781ce6e2c.png)

Inspired by this [blog post](https://sausheong.github.io/posts/how-to-build-a-simple-artificial-neural-network-with-go/).
