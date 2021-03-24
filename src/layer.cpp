#include <iostream>
#include <string>
#include <vector>
#include "layer.h"

using namespace std;

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
    out << rhs.a << endl;
    return out;
}















template <class T>
unsigned int Layer<T>::size() const
{
    return this->dz.size();
}



#include "layer_implementer.h"