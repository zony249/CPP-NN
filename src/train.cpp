#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "matrix.h"
#include "layer.h"
#include "model.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[])
{

    int epochs = 1;

    string train_filename = "MNIST-data-set/mnist_train.csv";
    string test_filename = "MNIST-data-set/mnist_test.csv";
    vector <pair<Matrix<float>, Matrix<float> > > trainset = read_MNIST_csv<float> (train_filename);
    vector <pair<Matrix<float>, Matrix<float> > > cvset = read_MNIST_csv<float> (test_filename);
    cout << "Num of training data: " << trainset.size() << endl;
    cout << "Num of cross val data: " << cvset.size() << endl << endl;
    //cout << trainset[8010].second << endl;

    Model<float> model(8e-4, 0.3);
    model.add_layer(Layer<float>(784, "linear"));
    //model.add_layer(Layer<float>(64, "relu"));
    model.add_layer(Layer<float>(128, "relu"));
    model.add_layer(Layer<float>(128, "relu"));
    //model.add_layer(Layer<float>(64, "relu"));
    model.add_layer(Layer<float>(10, "sigmoid"));
    model.connect();

    cout << model << endl;

    cout << "Press Enter to start training" << endl;
    string x;
    getline(cin, x);

    model.load_training_data(&trainset);
    model.load_cv_data(&cvset);

    //Layer<float> L(5, "relu");
    //L.z = Matrix<float>({-2, -1, 0, 1, 2}).tp();
    //cout << L.d_act(L.z) << endl; 

    for (int i = 0; i < epochs; i++)
    {   
        cout << "Epoch " << i+1 << " Starting... " << endl;
        this_thread::sleep_for(chrono::seconds(2));
        model.train(16);
        cout << endl;
        float cv_accuracy = model.evaluate();
        cout << "Cross Validation Accuracy: " << cv_accuracy * 100 << "%" << endl;
    }


    return 0;
}