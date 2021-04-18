#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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

        //Matrix<T> forward_prop(const unordered_map<string, Matrix<T> >& params, const Matrix<T>& x);

        T loss ( Matrix<T>& a, Matrix<T>& y) const;
        void train(int batch_size);
        void train_thread(int start, int end);

};



#endif