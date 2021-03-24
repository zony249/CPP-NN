#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include "matrix.h"
#include <string>

using namespace std;

template <class T> struct Layer;
template <class T> ostream& operator<<(ostream& out, const Layer<T>& rhs);

template <class T>
struct Layer
{
    // members
    Matrix<T> a;    // activated output
    Matrix<T> z;    // pre-activation
    Matrix<T> dz;   // Local layer error

    Matrix<T> W;    // Weights matrix
    Matrix<T> dW;   // error in weights

    Matrix<T> b;    // bias 
    Matrix<T> db;   // error in bias

    string activation;

    //methods
    Layer(unsigned int nodes, string activation);

    friend ostream& operator<< <T> (ostream& out, const Layer<T>& rhs);

    Matrix<T> act(const Matrix<T>& wsum);
    Matrix<T> d_act(const Matrix<T>& layer);
    unsigned int size() const;

};



#endif