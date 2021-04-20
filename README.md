# C++ Neural Network

## Overview

A simple implementation of a 4-layer dense neural network use to classify handwritten digits from the MNIST-DIGITS dataset. This neural network was written entirely in C++ using nothing but the standard library headers. This project has no real use other than being a fun project to keep me occupied for the past month.

## Neural Network Design

This (by default) is a 4-layer neural network (excluding the input layer), consisting of 3 hidden layers with 256 neurons each, as well as a final output layer with 10 neurons corresponding to the 10 classes the NN is predicting. A 4-layer design ensures reasonable training performance as well as being able to fit non-linear functions with high enough variance for the problem of classifying digits. All 3 hidden layers use the **ReLU** activation function for fast gradient descent, while the output layer uses **Sigmoid** for classification.  

The loss function is chosen automatically based on the last layer's activation function, which is either Cross-Entropy for Sigmoid or MSE for linear/ReLU. 