#include <iostream>
#include <string>
#include <cassert>
#include "matrix.h"

using namespace std;

/*
Initializes a matix of (rows x cols) with an initial value
Arguments:
    rows (uint): number of rows
    cols (uint): number of columns
*/
template <typename T>
Matrix<T>::Matrix(vector<unsigned int> shape, T init)
{
    this->nrows = shape[0];
    this->ncols = shape[1];
    this->mat = new T*[this->nrows];

    for (int i = 0; i < this->nrows; i++)
    {
        T* single_row = new T[this->ncols];
        for (int j = 0; j < this->ncols; j++)
        {
            single_row[j] = init;
        }
        this->mat[i] = single_row;
    }
}

/*
Copy constructor allowing for Matrix<T> A = B;
without copying over everything (i.e. the pointers)
*/
template <typename T>
Matrix<T>::Matrix(const Matrix& copy)
{
    this->nrows = copy.nrows;
    this->ncols = copy.ncols;
    this->mat = new T*[this->nrows];
    for (int i = 0; i < this->nrows; i++)
    {
        T* single_row = new T[this->ncols];
        for (int j = 0; j < this->ncols; j++)
        {
            single_row[j] = copy.mat[i][j];
        }
        this->mat[i] = single_row;
    }
}

template <typename T>
Matrix<T>::Matrix(const vector<T> elements)
{
    this->nrows = elements.size();
    this->ncols = 1;
    this->mat = new T*[elements.size()];
    for (int i = 0; i < elements.size(); i++)
    {
        T* single_row = new T[1];
        single_row[0] = elements[i];
        this->mat[i] = single_row;
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < this->nrows; i++)
    {
        delete[] this->mat[i];
    }
    delete[] this->mat;

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
        delete[] this->mat[i];
    }
    delete[] this->mat;

    this->mat = new T*[rhs.rows()];
    this->nrows = rhs.rows();
    this->ncols = rhs.cols();

    for (unsigned int i = 0; i < rhs.rows(); i++)
    {
        T* single_col = new T[rhs.cols()];
        for (unsigned int j = 0; j < rhs.cols(); j++)
        {
            single_col[j] = rhs[i][j];

        }
        this->mat[i] = single_col;
    }
    return *this;

}

template <typename T>
T* Matrix<T>::operator[](unsigned int index)
{
    return this->mat[index];

}
template <typename T>
const T* Matrix<T>::operator[](const unsigned int index) const
{
    return this->mat[index];

}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& rhs)
{
    
    assert(this->nrows == rhs.nrows && this->ncols == rhs.ncols);
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] + rhs.mat[i][j];
        }

    }
    return out;

}

template <typename T>
Matrix<T> Matrix<T>::operator+(T scalar)
{
    
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] + scalar;
        }

    }
    return out;

}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& rhs)
{
    assert(this->nrows == rhs.nrows && this->ncols == rhs.ncols);
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] - rhs.mat[i][j];
        }

    }
    return out;

}

template <typename T>
Matrix<T> Matrix<T>::operator-(T scalar)
{
    
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] - scalar;
        }

    }
    return out;

}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& rhs)
{
    assert(this->ncols == rhs.nrows);
    Matrix<T> out({this->nrows, rhs.ncols}, (T)0);

    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int k = 0; k < rhs.ncols; k++)
        {
            for (unsigned int j = 0; j < this->ncols; j++)
            {
                out.mat[i][k] += this->mat[i][j]*rhs.mat[j][k];
            }
        }
    }
    return out;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T scalar)
{
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] * scalar;
        }

    }
    return out;
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& rhs)
{
    assert(this->nrows == rhs.nrows && this->ncols == rhs.ncols);
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] / rhs.mat[i][j];
        }

    }
    return out;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T scalar)
{
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] / scalar;
        }

    }
    return out;
}












template <typename T>
unsigned int Matrix<T>::rows() const
{
    return this->nrows;
}
template <typename T>
unsigned int Matrix<T>::cols() const
{
    return this->ncols;
}

template <typename T>
unsigned int Matrix<T>::size() const
{
    return this->nrows * this->ncols;
}

template <typename T>
vector<unsigned int> Matrix<T>::shape() const
{
    vector<unsigned int> mat_shape = {this->nrows, this->ncols};
    return mat_shape;

}

template <typename T>
Matrix<T> Matrix<T>::tp()
{
    Matrix<T> out({this->ncols, this->nrows}, (T)0);
    for (unsigned int j = 0; j < this->ncols; j++)
    {
        for (unsigned int i = 0; i < this->nrows; i++)
        {
            out.mat[j][i] = this->mat[i][j];
        }
    }
    return out;
}


template <typename T>
Matrix<T> Matrix<T>::slice(vector<unsigned int> rows, vector<unsigned int> cols)
{
    if (rows.size() != 2 || cols.size() != 2)
    {
        cout << "arguments of Matrix<T>::slice(vector<int>, vector<int>) ";
        cout << "should be two vectors of size() == 2" << endl;
        throw -1;
    }
    int row_range = ((int)rows[1] - (int)rows[0]);
    int col_range = ((int)cols[1] - (int)cols[0]);

    if (row_range <= 0 || col_range <= 0)
    {
        cout << "Row range of ";
        cout << "(" << rows[0] << ", " << rows[1] << "), ";
        cout << "Col range of ";
        cout << "(" << cols[0] << ", " << cols[1] << ") ";
        cout << "is not allowed" << endl;
        throw -1;

    }
    

    Matrix<T> out({(unsigned int)row_range, (unsigned int)col_range}, (T)0);

    for (int i = 0; i < row_range; i++)
    {
        for (int j = 0; j < col_range; j++)
        {
            out.mat[i][j] = this->mat[rows[0] + i][cols[0] + j];
        }
    }

    return out;
}

template <typename T>
Matrix<T> Matrix<T>::flatten()
{
    unsigned int length = this->nrows * this->ncols;
    Matrix<T> out({length, 1}, (T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out.mat[j + i*this->ncols][0] = this->mat[i][j];
        }
    }
    return out;
}

template <typename T>
Matrix<T> Matrix<T>::get_row(unsigned int idx)
{
    Matrix<T> out = this->slice({idx, idx+1}, {0, this->ncols});
    return out;
}

template <typename T>
Matrix<T> Matrix<T>::set_row(unsigned int idx, Matrix<T> row)
{
    assert(row.nrows == 1);
    assert(row.ncols == this->ncols);
    Matrix<T> out = *this;

    for (int i = 0; i < this->ncols; i++)
    {
        out.mat[idx][i] = row.mat[0][i];
    }
    return out;
}

template <typename T>
Matrix<T> Matrix<T>::reshape(vector<unsigned int> shape)
{
    assert(this->nrows*this->ncols == shape[0] * shape[1]);
    Matrix<T> flat = this->flatten();
    Matrix<T> reshaped(shape, T(0));
    for (int i = 0; i < shape[0]; i++)
    {
        for (int j= 0; j < shape[1]; j++)
        {
            reshaped.mat[i][j] = flat.mat[j + i*shape[1]][0];
        }
    }
    return reshaped;
}


template <typename T> 
Matrix<T> Id(vector<unsigned int> shape)
{
    assert(shape[0] == shape[1]);
    Matrix<T> identity(shape, (T)0);
    for (int i = 0; i < shape[0]; i++)
    {
        identity[i][i] = (T)1;
    }
    return identity;
}

template <typename T>
Matrix<T> Matrix<T>::inv()
{
    assert(this->nrows == this->ncols);
    Matrix<T> copy = *this;
    Matrix<T> out = Id<T>({this->nrows, this->nrows});

    for (int j = 0; j < this->nrows; j++)
    {            
        T main_factor = copy.mat[j][j];
        Matrix<T> main_row = copy.get_row(j);
        main_row = main_row/main_factor;
        copy = copy.set_row(j, main_row);

        Matrix<T> i_row = out.get_row(j);
        i_row = i_row / main_factor;
        out = out.set_row(j, i_row);
        for (int i = 0; i < this->nrows; i++)
        {

            if (i != j)
            {
                Matrix<T> reduced_row = copy.get_row(i);
                T reducing_factor = copy.mat[i][j];
                reduced_row = reduced_row - main_row*reducing_factor;
                copy = copy.set_row(i, reduced_row);

                Matrix<T> reduced_row_i = out.get_row(i);
                reduced_row_i = reduced_row_i - i_row*reducing_factor;
                out = out.set_row(i, reduced_row_i);
            }
        }
    }
    return out;
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
    Matrix<float> helperFloat({1, 1}, 0.0);
    Matrix<double> helperDoub({1, 1}, 0.0);
    Matrix<int> helperInt({1, 1}, 0);
    cout << helperFloat;
    cout << helperInt;
    cout << helperDoub;
    helperFloat=helperFloat+1.0 + helperFloat/helperFloat - helperFloat*helperFloat/2.0;
    helperDoub=helperDoub+1.0 + helperDoub/helperDoub - helperDoub*helperDoub/2.0;
    helperInt=helperInt+1 + helperInt/helperInt - helperInt*helperInt/2;
    helperFloat[0][0] = 0.0;
    helperDoub[0][0] = 0.0;
    helperInt[0][0] = 0;
    Matrix<float> X = helperFloat;
    Matrix<double> Y = helperDoub;
    Matrix<int> Z = helperInt;
    X.rows();
    X.cols();
    X.size();
    X.shape();
    X.tp();
    X.flatten();
    Matrix<float> rX = X.get_row(0);
    X.set_row(0, rX);
    X.slice({1, 2}, {3, 4});
    X.reshape({1, 1});
    Y.rows();
    Y.cols();
    Y.size();
    Y.shape();
    Y.tp();
    Y.flatten();
    Matrix<double> rY = Y.get_row(0);
    Y.set_row(0, rY);
    Y.slice({1, 2}, {3, 4});
    Y.reshape({1, 1});
    Z.rows();
    Z.cols();
    Z.size();
    Z.shape();
    Z.tp();
    Z.flatten();
    Matrix<int> rZ = Z.get_row(0);
    Z.set_row(0, rZ);
    Z.slice({1, 2}, {3, 4});
    Z.reshape({1, 1});
    const Matrix<float> chelperFloat({1, 1}, 0.0);
    const Matrix<double> chelperDoub({1, 1}, 0.0);
    const Matrix<int> chelperInt({1, 1}, 0);
    cout << chelperFloat[0][0] << endl;
    cout << chelperDoub[0][0] << endl;
    cout << chelperInt[0][0] << endl;
    Matrix<float> A({0.0});
    Matrix<double> B({0.0});
    Matrix<int> C({0}); 
    Id<float>({1, 1});
    Id<double>({1, 1});
    Id<int>({1, 1});
    A.inv();
    B.inv();
    C.inv();
}