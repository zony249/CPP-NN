#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

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

};



#endif