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
        vector<pair<Matrix<T>, Matrix<T> > >* trainset;
        vector<pair<Matrix<T>, Matrix<T> > >* cvset;
    public:

        Model(double lr, double reg);
        Model();

        friend ostream& operator<< <T>(ostream& out, const Model<T>& rhs);

        void add_layer(Layer<T> layer);

        void connect();
        void load_training_data(vector<pair<Matrix<T>, Matrix<T> > >* dataset);
        void load_cv_data(vector<pair<Matrix<T>, Matrix<T> > >* dataset);

        void forward_prop(const Matrix<T>& x);
        void back_prop(const Matrix<T>& y);

};



#endif