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
            out << "Layer " << i <<   " size: " << size << endl;
    }
    return out;

}


template <class T>
void Model<T>::add_layer(Layer<T> layer)
{
    this->layers.push_back(layer);
}


#include "model_implementer.h"