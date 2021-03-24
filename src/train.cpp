#include <iostream>
#include <string>
#include "matrix.h"
#include "layer.h"
#include "model.h"

using namespace std;

int main(int argc, char* argv[])
{

    Layer<float> l0 (768, "relu");
    cout << l0 << endl;

    Model<float> model;
    model.add_layer(l0);
    model.add_layer(Layer<float>(100, "relu"));
    model.add_layer(Layer<float>(200, "relu"));
    model.add_layer(Layer<float>(100, "relu"));
    model.add_layer(Layer<float>(200, "relu"));    
    model.add_layer(Layer<float>(500, "relu"));
    model.add_layer(Layer<float>(1000, "relu"));
    model.add_layer(Layer<float>(500, "relu"));
    model.add_layer(Layer<float>(10, "relu"));

    cout << model << endl;

    return 0;
}