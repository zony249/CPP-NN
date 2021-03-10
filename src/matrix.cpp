#include <iostream>
#include <string>
#include "matrix.h"

using namespace std;

/*
Initializes a matix of (rows x cols) with an initial value
Arguments:
    rows (uint): number of rows
    cols (uint): number of columns
*/
template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, T init)
{
    this->nrows = rows;
    this->ncols = cols;
    this->mat = new T*[rows];

    for (int i = 0; i < rows; i++)
    {
        T* single_col = new T[cols];
        for (int j = 0; j < cols; j++)
        {
            single_col[j] = init;
        }
        this->mat[i] = single_col;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& copy)
{
    this->nrows = copy.nrows;
    this->ncols = copy.ncols;
    this->mat = new T*[this->nrows];
    for (int i = 0; i < this->nrows; i++)
    {
        T* single_col = new T[this->ncols];
        for (int j = 0; j < this->ncols; j++)
        {
            single_col[j] = copy.mat[i][j];
        }
        this->mat[i] = single_col;
    }
}


// =====  Operators ======== //



template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& rhs)
{
    for (int i = 0; i < rhs.nrows; i++)
    {
        for (int j = 0; j < rhs.ncols; j++)
        {
            out << rhs.mat[i][j];
            if (j != rhs.ncols-1) out << '\t';
        }
        out << endl;
    }
    return out;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> rhs)
{
    for (int i = 0; i < this->rows(); i++)
    {
        delete this->mat[i];
    }
    delete this->mat;

    this->mat = new T*[rhs.rows()];
    this->nrows = rhs.rows();
    this->ncols = rhs.cols();

    for (int i = 0; i < rhs.rows(); i++)
    {
        T* single_col = new T[rhs.cols()];
        for (int j = 0; j < rhs.cols(); j++)
        {
            single_col[j] = rhs[i][j];

        }
        this->mat[i] = single_col;
    }
    return *this;

}

template <typename T>
T* Matrix<T>::operator[](int index)
{
    return this->mat[index];

}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& rhs)
{
    // insert assert statement
    Matrix<T> out(this->nrows, this->ncols,(T)0);
    for (int i = 0; i < this->nrows; i++)
    {
        for (int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] + rhs.mat[i][j];
        }

    }
    return out;

}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& rhs)
{
    // insert assert statement
    Matrix<T> out(this->nrows, this->ncols,(T)0);
    for (int i = 0; i < this->nrows; i++)
    {
        for (int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] - rhs.mat[i][j];
        }

    }
    return out;

}

template <typename T>
unsigned int Matrix<T>::rows()
{
    return this->nrows;
}
template <typename T>
unsigned int Matrix<T>::cols()
{
    return this->ncols;
}


/*
This function is never invoked;
Its sole purpose is to implement
various template types for the matrix
class so that the linker knows how to 
link with train.o

Seriously, templates are cool but 
the linker sucks
*/
void link_helper()
{
    Matrix<float> helperFloat(1, 1, 0.0);
    Matrix<double> helperDoub(1, 1, 0.0);
    Matrix<int> helperInt(1, 1, 0);
    cout << helperFloat;
    cout << helperInt;
    cout << helperDoub;
    helperFloat=helperFloat + helperFloat - helperFloat;
    helperDoub=helperDoub + helperDoub - helperDoub;
    helperInt=helperInt + helperInt - helperInt;
    helperFloat[0][0] = 0.0;
    helperDoub[0][0] = 0.0;
    helperInt[0][0] = 0;
    Matrix<float> X = helperFloat;
    Matrix<double> Y = helperDoub;
    Matrix<int> Z = helperInt;
}