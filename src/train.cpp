#include <iostream>
#include <string>
#include <vector>
#include "matrix.h"
#include "layer.h"
#include "model.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[])
{

    string train_filename = "MNIST-data-set/mnist_train.csv";
    string test_filename = "NMIST-data-set/mnist_test.csv";
    // vector <pair<Matrix<float>, Matrix<float> > > train = read_MNIST_csv<float> (train_filename);
    // cout << "Num of training data: " << train.size() << endl;
    // cout << train[8010].second << endl;

    // Model<float> model;
    // model.add_layer(Layer<float>(784, "linear"));
    // model.add_layer(Layer<float>(256, "relu"));
    // model.add_layer(Layer<float>(256, "relu"));
    // model.add_layer(Layer<float>(10, "sigmoid"));
    // model.connect();

    // cout << model << endl;


    // Matrix<float> x = train[4].first.tp();
    // model.forward_prop(x);

    Model<float> model;
    model.add_layer(Layer<float> (4, "linear"));
    model.add_layer(Layer<float> (6, "relu"));
    model.add_layer(Layer<float> (7, "relu"));
    model.add_layer(Layer<float> (8, "relu"));
    model.add_layer(Layer<float> (2, "sigmoid"));
    model.connect();

    Matrix<float> x = Matrix<float>({1., 2., 3., 4.}).tp();
    Matrix<float> y = Matrix<float>({1, 0}).tp();

    vector<pair<Matrix<float>, Matrix<float> > > testdat = {{x, y}};
    model.load_training_data(&testdat);

    model.train(16);


    return 0;
}