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
    vector <pair<Matrix<float>, Matrix<float> > > trainset = read_MNIST_csv<float> (train_filename);
    cout << "Num of training data: " << trainset.size() << endl;
    //cout << trainset[8010].second << endl;

    Model<float> model(3e-2, 0.2);
    model.add_layer(Layer<float>(784, "linear"));
    model.add_layer(Layer<float>(128, "relu"));
    model.add_layer(Layer<float>(128, "relu"));
    model.add_layer(Layer<float>(10, "sigmoid"));
    model.connect();

    cout << model << endl;

    model.load_training_data(&trainset);
    model.train(64);


    //Matrix<float> x = train[4].first.tp();
    //model.forward_prop(x);

    // Model<float> model;
    // model.add_layer(Layer<float> (4, "linear"));
    // model.add_layer(Layer<float> (6, "relu"));
    // model.add_layer(Layer<float> (7, "relu"));
    // model.add_layer(Layer<float> (8, "relu"));
    // model.add_layer(Layer<float> (2, "sigmoid"));
    // model.connect();

    // Matrix<float> x = Matrix<float>({1., 2., 3., 4.}).tp();
    // Matrix<float> y = Matrix<float>({1, 0}).tp();

    // vector<pair<Matrix<float>, Matrix<float> > > testdat = {{x, y}};
    // model.load_training_data(&testdat);

    // model.train(16);

    // Matrix<float> C({3, 3}, 3);
    // Matrix<float> D({3, 3}, 4);
    // cout << C - D << endl;


    // Matrix<float> E({30, 40, 50, 60, 70});
    // cout << sigmoid(E) << endl;

    return 0;
}