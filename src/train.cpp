#include <iostream>
#include <string>
#include "matrix.h"
#include "layer.h"
#include "model.h"
<<<<<<< HEAD
=======
#include "utils.h"
>>>>>>> fce2300 (Nuked repo. retransferring files)

using namespace std;

int main(int argc, char* argv[])
{

<<<<<<< HEAD
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

=======
    string train_filename = "MNIST data set/mnist_train.csv";
    string test_filename = "NMIST data set/mnist_test.csv";
    vector <pair<Matrix<float>, Matrix<float> > > train = read_MNIST_csv<float> (train_filename);
    cout << "Num of training data: " << train.size() << endl;
    // cout << train[8010].second << endl;

    Model<float> model;
    model.add_layer(Layer<float>(784, "linear"));
    model.add_layer(Layer<float>(256, "relu"));
    model.add_layer(Layer<float>(256, "relu"));
    model.add_layer(Layer<float>(10, "sigmoid"));
    model.connect();

    cout << model << endl;

    cout << "testing exp()" << endl;
    vector<float> items = {1, 2, 3, 4, 5, 6};
    Matrix<float> M = Matrix<float>(items).reshape({2, 3});
    cout << "M: " << endl;
    cout << M << endl;
    cout << "exp(M)" << endl;
    cout << exp(M) << endl;

    cout << "testing sigmoid()" << endl;
    vector<float> items2 = {-2, -1, 0, 1, 2};
    Matrix<float> N = Matrix<float>(items2);
    cout << "N:" << endl;
    cout << N << endl;
    cout << "sigmoid(N):" << endl;
    cout << sigmoid(N) << endl;

    cout << "testing relu()" << endl;
    vector<float> items3 = {-2, -1, 0, 1, 2};
    Matrix<float> P = Matrix<float>(items3);
    cout << "P:" << endl;
    cout << P << endl;
    cout << "relu(N):" << endl;
    cout << relu(N) << endl;

>>>>>>> fce2300 (Nuked repo. retransferring files)
    return 0;
}