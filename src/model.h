#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

template <class T> class Model;
template <class T> ostream& operator<<(ostream&, const Model<T>&);


template <class T>
class Model
{
    private:
        vector<Layer<T> > layers;
        double lr;
        double reg;
    public:

        Model(double lr, double reg);
        Model();

        friend ostream& operator<< <T>(ostream& out, const Model<T>& rhs);

        void add_layer(Layer<T> layer);
        void connect();
        void load_training_data(vector<pair<Matrix<T>, Matrix<T> > > );

        void forward_prop(Matrix<T> x);
        void back_prop(Matrix<T> y);

};



#endif