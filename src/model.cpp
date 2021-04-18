#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <thread>
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
    this->cvset = dataset;
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
        this->layers[i].z = dot(this->layers[i].W, this->layers[i-1].a) + this->layers[i].b;
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
    this->layers[last].dW += dot(this->layers[last].dz, this->layers[last-1].a.tp());
    this->layers[last].db += this->layers[last].dz; 

    // all other layers (except for input)
    for (int i = last - 1; i >= 1; i--)
    {
        this->layers[i].dz = dot(this->layers[i+1].W.tp(), this->layers[i+1].dz) *
                            this->layers[i].d_act(this->layers[i].z);
        //cout << "(" << this->layers[i].dW.rows() << ", " << this->layers[i].dW.cols() << ")" << endl;
        this->layers[i].dW += dot(this->layers[i].dz, this->layers[i-1].a.tp());
        this->layers[i].db += this->layers[i].dz; 
    }

}

template <class T>
T Model<T>::loss(Matrix<T>& a, Matrix<T>& y) const
{
    unsigned int n = a.rows();
    T single_cost;
    int last = this->layers.size()-1;
    if (this->layers[last].activation == "sigmoid")
    {
        //cout << -y*log(a)-(1-y)*log(1-a) << endl;
        single_cost = sum<T>(-y*log(a)-(1-y)*log(1-a), 0)[0][0]/n;
    } 
    else if (this->layers[last].activation == "relu")
    {
        single_cost = sum<T>((a-y)*(a-y), 0)[0][0]/n;
    }
       
    return single_cost;
}

template <class T>
void Model<T>::train(int batch_size)
{
    // trainset has to be loaded to train
    assert(this->trainset != NULL);

    int batch_count = 0;
    int dataset_size = (*this->trainset).size();
    int last = this->layers.size() - 1;
    for (int i = 0; i < dataset_size; i++)
    {
        if (batch_count > batch_size)
        {
            batch_count = 0;
            for (int i = 1; i <= last; i++)
            {
                this->layers[i].W -= this->lr * (this->layers[i].dW + this->reg * this->layers[i].W)/(T)batch_size;
                this->layers[i].b -= this->lr * (this->layers[i].db)/(T)batch_size;
                this->layers[i].dW = zeros<T>(this->layers[i].W.shape());
                this->layers[i].db = zeros<T>(this->layers[i].b.shape());
                
            }

        }
        Matrix<T> x = (*this->trainset)[i].first.tp();
        Matrix<T> y = (*this->trainset)[i].second.tp();
        
        this->forward_prop(x);
        cout << "Training Iteration: " << i << ", ";
        cout << "Loss: " << this->loss(this->layers[last].a, y) << endl;
        //cout << this->layers[last].a << endl;
        //cout << y << endl;
        this->back_prop(y);
        batch_count ++;
    }
}

// template <class T>
// void Model<T>::train(int batch_size)
// {
//     int nthreads = min(8, batch_size);
//     int tset_size = (*this->trainset).size();
    
//     int dat_r = tset_size%batch_size;   // remaining datapoints at the end
//     int dat_divs = (tset_size - dat_r)/batch_size;  // number of times to load a batch
//     cout << "Dataset size: " << tset_size << endl;
//     for (int i = 0; i < dat_divs; i++)
//     {
//         int num_to_process = batch_size;
//         if (i == dat_divs -1)
//             num_to_process = (batch_size + dat_r);

//         // remainder to add to the end of the last thread
//         // This is to ensure that if the dataset size is not 
//         // divisible by the batch size, all datapoints will be
//         // used for training.
//         int r = num_to_process%nthreads;
//         int per_thread = (num_to_process - r)/nthreads;
        
//         int t_start = i*batch_size;
//         int t_end;

//         vector<thread> th;

//         // cout << i << ": " << endl;
//         for (int j = 0; j < nthreads; j++)
//         {
//             t_end = t_start + per_thread;
//             if (j == nthreads - 1)
//                 t_end = i*batch_size + num_to_process;

//             //cout << t_start << ", " << t_end << endl;
//             th.push_back(thread(&Model<T>::train_thread, this, t_start, t_end));

//             t_start = t_end; 
//         } 

//         for (int j = 0; j < nthreads; j++)
//         {
//             th[j].join();
//         }
//         //cout << endl << endl;
//     }
// }

template <class T>
void Model<T>::train_thread(int start, int end)
{
    for (int i = start; i < end; i++)
    {
        Matrix<T> x = (*this->trainset)[i].first.tp();
        Matrix<T> y = (*this->trainset)[i].second.tp();
        
        this->forward_prop(x);
        //this->back_prop(y);
    }
}
#include "model_implementer.h"