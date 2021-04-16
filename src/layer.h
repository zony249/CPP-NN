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


    // calculates the activation based on this->activation
    Matrix<T> act(const Matrix<T>& wsum);
    // calculates the derivative of the activation based on this->activation
    Matrix<T> d_act(const Matrix<T>& layer);
    void init_params();

    unsigned int size() const;

};



template <class T>
Layer<T>::Layer(unsigned int nodes, string activation)
{
    this->z = Matrix<T>({nodes, 1}, (T)0);
    this->dz = Matrix<T>({nodes, 1}, (T)0);
    this->a = Matrix<T>({nodes, 1}, (T)0);
    this->activation = activation;

}

template <class T>
ostream& operator<<(ostream& out, const Layer<T>& rhs)
{
    out << rhs.a;
    return out;
}

template <class T>
Matrix<T> Layer<T>::act(const Matrix<T>& wsum)
{
    if (this->activation == "sigmoid")
    {
        return sigmoid(wsum);
    }
    else if (this->activation == "relu")
    {
        return relu(wsum);
    }
    // linear activation
    return wsum;
}

template <class T>
Matrix<T> Layer<T>::d_act(const Matrix<T>& z_val)
{
    Matrix<T> out(z_val.shape(), 1);
    if (this->activation == "sigmoid")
    {
        return sigmoid(z_val)*(1 - sigmoid(z_val));
    } 
    else if (this->activation == "relu")
    {
        for (int i = 0; i < z_val.rows(); i++)
        {
            if (z_val[i][0] > (T)0) out[i][0] = (T)1;
            else out[i][0] = (T)0;
        }   
        return out;
    }  
    return out; 

}










/*
Initializes the weights randomly, and sets bias to 0.
*/
template <class T>
void Layer<T>::init_params()
{
    assert(this->W.size() != 0);
    this->W = randmat<T>(this->W.shape(), 0.02);
    this->b = zeros<T>(this->b.shape());

    this->dW = zeros<T>(this->W.shape());
    this->db = zeros<T>(this->b.shape());
    this->dz = zeros<T> (this->z.shape());
}

template <class T>
unsigned int Layer<T>::size() const
{
    return this->z.size();
}


#endif