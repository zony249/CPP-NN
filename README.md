# C++ Neural Network

## Overview

A simple implementation of a 3-layer dense neural network use to classify handwritten digits from the MNIST-DIGITS dataset. This neural network was written entirely in C++ using nothing but the standard library headers. This project has no real use other than being a fun project to keep me occupied for the past month.



## Neural Network Design

This (by default) is a 3-layer neural network (excluding the input layer), consisting of 2 hidden layers with 128 neurons each, as well as a final output layer with 10 neurons corresponding to the 10 classes of digits. A 3-layer design ensures reasonable training performance as well as being able to fit non-linear functions with high enough variance for the problem of classifying digits. All 3 hidden layers use the **ReLU** activation function for fast gradient descent, while the output layer uses **Sigmoid** for classification.  

For a full breakdown of the NN, the `train` executable will print out the model summary prior to training:

```
=================== Model Summary ====================
Learning Rate: 0.0008
Regularization (l2): 0.3

Input size: 784
Layer 1 size: 128       W1.shape = (128, 784)   b1.shape = (128, 1)     Activation: relu
Layer 2 size: 128       W2.shape = (128, 128)   b2.shape = (128, 1)     Activation: relu
Layer 3 size: 10        W3.shape = (10, 128)    b3.shape = (10, 1)      Activation: sigmoid

```

## Before You Compile

Due to size limitations, `mnist_train.csv` and `mnist_test.csv` are not included in the repo. You can download `mnist_train.csv` and `mnist_test.csv` from [https://www.kaggle.com/oddrationale/mnist-in-csv](https://www.kaggle.com/oddrationale/mnist-in-csv) and place them in the `MNIST-data-set/` directory. `train` is set to read from that directory by default.

## Building and Running the Project

Build the project by running the following:
```bash
$ make -j2
```
After the project has been compiled, you can run the `train` executable from the main working directory:
```bash
$ ./train
```
While running, `train` will stop after displaying the Model Summary and prompt for your acknowlegement to continue training. Press `Enter` to begin training. Training will take a few minutes to complete, and then will evaluate the network accuracy by inferencing on the test set.

## Notice
This program is still under development. Future additions include serializing the model and loading a trained model, as well as command line arguments. If you have any suggestions, feel free to send them to me.

## License
```
Copyright (C) 2021 Zony Yu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
```
