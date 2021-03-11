#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

// Forward declaring the Matrix class to incoporate a template operator<<
template <typename T> class Matrix;
template <typename T> ostream& operator<<(ostream& , const Matrix<T>& );
template <typename T> Matrix<T> Id(vector<unsigned int>);

template <typename T>
class Matrix
{
    private:
        T** mat;
        unsigned int nrows, ncols;
    public:
        Matrix(vector<unsigned int> shape,  T init);
        Matrix(const Matrix& copy);
        Matrix(const vector<T> elements);
        ~Matrix();

        friend ostream& operator<< <T>(ostream& out, const Matrix<T>& rhs);
        Matrix<T>& operator=(Matrix<T> rhs);
        T* operator[](unsigned int index);
        const T* operator[](const unsigned int index) const;
        Matrix<T> operator+(const Matrix& rhs);
        Matrix<T> operator+(T scalar);
        Matrix<T> operator-(const Matrix& rhs);
        Matrix<T> operator-(T scalar);
        Matrix<T> operator*(const Matrix& rhs);
        Matrix<T> operator*(const T scalar);
        Matrix<T> operator/(const Matrix& rhs);
        Matrix<T> operator/(const T scalar);

        unsigned int rows() const;
        unsigned int cols() const;
        unsigned int size() const;
        vector<unsigned int> shape() const;
        Matrix<T> tp();
        Matrix<T> slice(vector<unsigned int> rows, vector<unsigned int>cols);
        Matrix<T> flatten();
        Matrix<T> get_row(unsigned int idx);
        Matrix<T> set_row(unsigned int idx, Matrix<T> row);
        Matrix<T> reshape(vector<unsigned int> shape);
        Matrix<T> inv();

};



#endif