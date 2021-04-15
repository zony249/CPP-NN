#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "layer.h"
#include "model.h"

using namespace std;

template <class T>
Model<T>::Model(double lr, double reg)
{
    this->lr = lr;
    this->reg = reg;
    this->trainset = NULL;
    this->cvset = NULL;
}

/*
Default constructor for default learning rate and regularization values
*/
template <class T>
Model<T>::Model()
{
    this->lr = 1e-2;
    this->reg = 0.0;
    this->trainset = NULL;
    this->cvset = NULL;
}


template <class T>
ostream& operator<<(ostream& out, const Model<T>& rhs)
{
    out << "Model Summary:" << endl;
    for (int i = 0; i < rhs.layers.size(); i++)
    {
        unsigned int size = rhs.layers[i].size();
        if (i == 0)
            out << "Input size: " << size << endl;
        else
        {
            out << "Layer " << i << " size: " << size << '\t';
            out << "W"<< i <<".shape = " << "(" <<rhs.layers[i].W.shape()[0] << ", ";
            out << rhs.layers[i].W.shape()[1] << ")" << '\t';
            out << "b" << i << ".shape = "<< "(" << rhs.layers[i].b.shape()[0] << ", ";
            out << rhs.layers[i].b.shape()[1] << ")" << '\t';
            out << "Activation: " << rhs.layers[i].activation << endl;
        }

    }
    return out;

}


template <class T>
void Model<T>::add_layer(Layer<T> layer)
{
    this->layers.push_back(layer);
}



/*
Loops through each layer, setting the shape of each layer's 
Weights and biases, and then initializes them. In other words,
this method connects all layers together.
*/
template <class T>
void Model<T>::connect()
{
    for (int i = 1; i < this->layers.size(); i++)
    {
        this->layers[i].W = Matrix<T>({this->layers[i].size(), this->layers[i-1].size()}, (T)0);
        this->layers[i].b = Matrix<T>({this->layers[i].size(), 1}, (T)0);
        this->layers[i].init_params();
    }
}

template <class T>
void Model<T>::load_training_data(vector<pair<Matrix<T>, Matrix<T> > >* dataset)
{
    this->trainset = dataset;
}
template <class T>
void Model<T>::load_cv_data(vector<pair<Matrix<T>, Matrix<T> > >* dataset)
{
    this->cvset = cvset;
}



template <class T>
void Model<T>::forward_prop(const Matrix<T>& x)
{
    // assumes x is a column vector
    assert(x.shape() == this->layers[0].a.shape());

    this->layers[0].a = x;
    // cout << "Input: \n" << this->layers[0].a << endl;
    for (int i = 1; i < this->layers.size(); i++)
    {
        this->layers[i].z = this->layers[i].W.dot(this->layers[i-1].a) + this->layers[i].b;
        this->layers[i].a = this->layers[i].act(this->layers[i].z);
        // cout << "layer " << i << ":" << endl;
        // cout << "W: \n" << this->layers[i].W << endl;
        // cout << "z: \n" << this->layers[i].z << endl;
        // cout << "a: \n" << this->layers[i].a << endl;
    }
}


template <class T>
void Model<T>::back_prop(const Matrix<T>& y)
{
    int last = this->layers.size()-1;
    assert(y.rows() == this->layers[last].a.rows());
    // output layer
    this->layers[last].dz = this->layers[last].a - y;
    this->layers[last].dW += this->layers[last].dz.dot(this->layers[last-1].a.tp());
    this->layers[last].db += this->layers[last].dz; 

    // all other layers (except for input)
    for (int i = last - 1; i >= 1; i--)
    {
        this->layers[i].dz = this->layers[i+1].W.tp().dot(this->layers[i+1].dz) *
                            this->layers[i].d_act(this->layers[i].z);
        //cout << "(" << this->layers[i].dW.rows() << ", " << this->layers[i].dW.cols() << ")" << endl;
        this->layers[i].dW += this->layers[i].dz.dot(this->layers[i-1].a.tp());
        this->layers[i].db += this->layers[i].dz; 
    }

}

#include "model_implementer.h"