#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>

using namespace std;

// Forward declaring the Matrix class to incoporate a template operator<<
template <typename T> class Matrix;
template <typename T> ostream& operator<<(ostream& , const Matrix<T>& );

template <typename T>
class Matrix
{
    private:
        T** mat;
        unsigned int nrows, ncols;
    public:
        Matrix(unsigned int rows, unsigned int cols, T init);
        Matrix(const Matrix& copy);

        friend ostream& operator<< <T>(ostream& out, const Matrix<T>& rhs);
        Matrix<T>& operator=(Matrix<T> rhs);
        T* operator[](int index);
        Matrix<T> operator+(const Matrix& rhs);
        Matrix<T> operator-(const Matrix& rhs);

        unsigned int rows();
        unsigned int cols();

};


#endif