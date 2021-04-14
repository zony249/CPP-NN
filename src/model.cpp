#include <iostream>
#include <vector>
#include <string>
#include "layer.h"
#include "model.h"

using namespace std;

template <class T>
Model<T>::Model(double lr, double reg)
{
    this->lr = lr;
    this->reg = reg;
}

<<<<<<< HEAD
=======

/*
Default constructor for default learning rate and regularization values
*/
>>>>>>> fce2300 (Nuked repo. retransferring files)
template <class T>
Model<T>::Model()
{
    this->lr = 1e-2;
    this->reg = 0.0;
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
<<<<<<< HEAD
            out << "Layer " << i <<   " size: " << size << endl;
=======
        {
            out << "Layer " << i << " size: " << size << '\t';
            out << "W"<< i <<".shape = " << "(" <<rhs.layers[i].W.shape()[0] << ", ";
            out << rhs.layers[i].W.shape()[1] << ")" << '\t';
            out << "b" << i << ".shape = "<< "(" << rhs.layers[i].b.shape()[0] << ", ";
            out << rhs.layers[i].b.shape()[1] << ")" << '\t';
            out << "Activation: " << rhs.layers[i].activation << endl;
        }
>>>>>>> fce2300 (Nuked repo. retransferring files)
    }
    return out;

}


template <class T>
void Model<T>::add_layer(Layer<T> layer)
{
    this->layers.push_back(layer);
}


<<<<<<< HEAD
=======
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

>>>>>>> fce2300 (Nuked repo. retransferring files)
#include "model_implementer.h"