#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <math.h>


using namespace std;

// Forward declaring the Matrix class to incoporate a template operator<<
template <typename T> class Matrix;
template <typename T> ostream& operator<<(ostream& , const Matrix<T>& );
template <typename T, typename K> Matrix<T> operator+(K, const Matrix<T>&);
template <typename T, typename K> Matrix<T> operator-(K, const Matrix<T>&);
template <typename T, typename K> Matrix<T> operator*(K, const Matrix<T>&);
template <typename T, typename K> Matrix<T> operator/(K, const Matrix<T>&);
template <typename T> Matrix<T> Id(vector<unsigned int>);
template <typename T, typename K> Matrix<T> randmat(vector<unsigned int>, K);
template <typename T> Matrix<T> zeros(vector<unsigned int>);
template <typename T> Matrix<T> dot(const Matrix<T>&, const Matrix<T>&);
template <typename T> Matrix<T> sigmoid(const Matrix<T>&);
template <typename T> Matrix<T> exp(const Matrix<T>&);
template <typename T, typename K> T max(T, K);
template <typename T> Matrix<T> relu(const Matrix<T>&);
template <typename T> T log(T n);
template <typename T> Matrix<T> log(const Matrix<T>&);
template <typename T> Matrix<T> sum(const Matrix<T>&, int);



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
        Matrix();
        ~Matrix();

        friend ostream& operator<< <T>(ostream& out, const Matrix<T>& rhs);
        Matrix<T>& operator=(Matrix<T> rhs);
        T* operator[](unsigned int index);
        const T* operator[](const unsigned int index) const;
        Matrix<T> operator+(const Matrix& rhs);
        Matrix<T> operator+(T scalar);
        Matrix<T> operator-(const Matrix& rhs);
        Matrix<T> operator-(T scalar);
        Matrix<T> operator-() const;
        Matrix<T> operator*(const Matrix& rhs);
        Matrix<T> operator*(const T scalar);
        Matrix<T> operator/(const Matrix& rhs);
        Matrix<T> operator/(const T scalar);
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T>& operator-=(const Matrix<T>& rhs);

        unsigned int rows() const;
        unsigned int cols() const;
        unsigned int size() const;
        vector<unsigned int> shape() const;
        Matrix<T> tp();
        Matrix<T> slice(vector<unsigned int> rows, vector<unsigned int>cols);
        Matrix<T> flatten();
        Matrix<T> get_row(unsigned int idx);
        void set_row(unsigned int idx, const Matrix<T>& row);
        Matrix<T> reshape(vector<unsigned int> shape);
        Matrix<T> inv();

};


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
    this->nrows = 1;
    this->ncols = elements.size();
    this->mat = new T*[1];
    T* single_row = new T[elements.size()];
    for (int i = 0; i < elements.size(); i++)
    {
        single_row[i] = elements[i];
    }
    this->mat[0] = single_row;
}

template <typename T>
Matrix<T>::Matrix()
{
    this->ncols = 0;
    this->nrows = 0;
    this->mat = NULL;

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
            out  << scientific << rhs.mat[i][j];
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

template <typename T, typename K> 
Matrix<T> operator+(K scalar, const Matrix<T>& rhs)
{
    Matrix<T> out(rhs.shape(), T(0));
    for (unsigned int i = 0; i < rhs.rows(); i++)
    {
        for (unsigned int j = 0; j < rhs.cols(); j++)
        {
            out[i][j] = (T)scalar + rhs[i][j];
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
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> out({this->nrows, this->ncols}, 0);
    for (int i = 0; i < this->nrows; i++)
    {
        for (int j = 0; j < this->ncols; j++)
        {
            out[i][j] = -this->mat[i][j];
        }
    }
    return out;
}

template <typename T, typename K> 
Matrix<T> operator-(K scalar, const Matrix<T>& rhs)
{
    Matrix<T> out(rhs.shape(), T(0));
    for (unsigned int i = 0; i < rhs.rows(); i++)
    {
        for (unsigned int j = 0; j < rhs.cols(); j++)
        {
            out[i][j] = (T)scalar - rhs[i][j];
        }

    }
    return out;

}


/* Element-wise Multiplication. For matrix multiplication, 
see Matrix<T>::dot(const Matrix<T>&)
Arguments:
    rhs (const Matrix<T>&): right hand side of the * sign.
Returns:
    out (Matrix<T>): the element-wise product of this and rhs.
*/
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
    assert(this->nrows == rhs.nrows && this->ncols == rhs.ncols);
    Matrix<T> out({this->nrows, this->ncols},(T)0);
    for (unsigned int i = 0; i < this->nrows; i++)
    {
        for (unsigned int j = 0; j < this->ncols; j++)
        {
            out[i][j] = this->mat[i][j] * rhs.mat[i][j];
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

template <typename T, typename K> 
Matrix<T> operator*(K scalar, const Matrix<T>& rhs)
{
    Matrix<T> out(rhs.shape(), T(0));
    for (unsigned int i = 0; i < rhs.rows(); i++)
    {
        for (unsigned int j = 0; j < rhs.cols(); j++)
        {
            out[i][j] = (T)scalar * rhs[i][j];
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

template <typename T, typename K> 
Matrix<T> operator/(K scalar, const Matrix<T>& rhs)
{
    Matrix<T> out(rhs.shape(), T(0));
    for (unsigned int i = 0; i < rhs.rows(); i++)
    {
        for (unsigned int j = 0; j < rhs.cols(); j++)
        {
            out[i][j] = (T)scalar / rhs[i][j];
        }

    }
    return out;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    assert(rhs.ncols == this->ncols && rhs.nrows == this->nrows);
    for (int i = 0; i < this->nrows; i++)
    {
        for (int j = 0; j < this->ncols; j++)
        {
            this->mat[i][j] += rhs.mat[i][j];
        }
    }
    return *this;

}
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
    assert(rhs.ncols == this->ncols && rhs.nrows == this->nrows);
    for (int i = 0; i < this->nrows; i++)
    {
        for (int j = 0; j < this->ncols; j++)
        {
            this->mat[i][j] -= rhs.mat[i][j];
        }
    }
    return *this;

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

/*
Sets a row of a Matrix to a (1 x m) Matrix representing a row
Arguments:
    idx (uint): the index of the row to insert into
    row (const Matrix<T>&): the (1 x m) row slice
*/
template <typename T>
void Matrix<T>::set_row(unsigned int idx, const Matrix<T>& row)
{
    assert(row.nrows == 1);
    assert(row.ncols == this->ncols);

    for (int i = 0; i < this->ncols; i++)
    {
        this->mat[idx][i] = row.mat[0][i];
    }
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

template <typename T, typename K>
Matrix<T> randmat(vector<unsigned int> shape, K range)
{
    Matrix<T> out(shape, T(0));
    for (int i = 0; i < out.rows(); i++)
    {
        for (int j = 0; j < out.cols(); j++)
        {
            out[i][j] = (T)((double)rand()/(double)RAND_MAX * (double)range);
        }

    }
    return out;
}

template <class T>
Matrix<T> zeros(vector<unsigned int> shape)
{
    Matrix<T> out(shape, (T)0);
    return out;
}


/*
Calculates the matrix inverse of a square matrix.
This method uses gaussian-elimination method to 
reach the identity matrix. Note that not all square 
matrices are invertable. If not invertable, throws 
SIGABRT.
*/
template <typename T>
Matrix<T> Matrix<T>::inv()
{
    assert(this->nrows == this->ncols);
    Matrix<T> copy = *this;
    Matrix<T> out = Id<T>({this->nrows, this->nrows});

    for (int j = 0; j < this->nrows; j++)
    {   
        // Normalizes an eliminating row with the 
        // value at copy[j][j] to get a leading 1.
        T main_factor = copy.mat[j][j];
        Matrix<T> main_row = copy.get_row(j);
        main_row = main_row/main_factor;
        copy.set_row(j, main_row);

        // performs the same action to the identity matrix
        Matrix<T> i_row = out.get_row(j);
        i_row = i_row / main_factor;
        out.set_row(j, i_row);
        for (int i = 0; i < this->nrows; i++)
        {

            if (i != j)
            {
                // All other rows that are not the elimination row
                // will get a column eliminated by the leading 1
                Matrix<T> reduced_row = copy.get_row(i);
                T reducing_factor = copy.mat[i][j];
                reduced_row = reduced_row - main_row*reducing_factor;
                copy.set_row(i, reduced_row);

                // do the same with the identity matrix
                Matrix<T> reduced_row_i = out.get_row(i);
                reduced_row_i = reduced_row_i - i_row*reducing_factor;
                out.set_row(i, reduced_row_i);
            }
        }
    }

    // checks if any number is NaN, which implies singularity
    for (int i = 0; i < this->nrows; i++)
    {
        if (isnan(this->mat[i][i]))
        {
            cout << "Matrix is not invertible" << endl;
            throw -1;
        }
    }
    return out;
}


template <typename T> 
Matrix<T> dot(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    assert(lhs.cols() == rhs.rows());
    Matrix<T> out({lhs.rows(), rhs.cols()}, (T)0);

    for (unsigned int i = 0; i < lhs.rows(); i++)
    {
        for (unsigned int k = 0; k < rhs.cols(); k++)
        {
            for (unsigned int j = 0; j < lhs.cols(); j++)
            {
                out[i][k] += lhs[i][j]*rhs[j][k];
            }
        }
    }
    return out;
}


template <typename T> 
Matrix<T> exp(const Matrix<T>& arg)
{
    Matrix<T> out(arg.shape(), (T)0);
    for (int i = 0; i < arg.rows(); i++)
    {
        for (int j = 0; j < arg.cols(); j++)
        {
            out[i][j] = exp(arg[i][j]);
        }

    }
    return out;
}
template <typename T>
Matrix<T> sigmoid(const Matrix<T>& arg)
{
    Matrix<T> out = 1/(1 + exp(-arg));
    return out;
}

template <typename T, typename K>
T max(T a, K b)
{
    if ((K)a > b) return (K)a;
    else return b;
}

template <typename T>
Matrix<T> relu(const Matrix<T>& arg)
{
    Matrix<T> out(arg.shape(), (T)0);
    for (int i = 0; i < arg.rows(); i++)
    {
        for (int j = 0; j < arg.cols(); j++)
        {
            out[i][j] = max(0.0, arg[i][j]);
        }
    
    }
    return out;
}

template <typename T>
T log(T n)
{
    return log(n)/log((T)2.718281828459045);
}

template <typename T>
Matrix<T> log(const Matrix<T>& arg)
{
    Matrix<T> out = zeros<T>(arg.shape());
    for (int i = 0; i < arg.rows(); i++)
    {
        for (int j = 0; j < arg.cols(); j++)
        {
            out[i][j] = log(arg[i][j]);
        }
    }
    return out;
}

template <typename T> 
Matrix<T> sum(const Matrix<T>& arg, int axis)
{
    assert(axis == 1 || axis == 0);
    Matrix<T> out;
    if (axis == 1)
    {
        out = zeros<T>({arg.rows(), 1});
        for (int i = 0; i < arg.rows(); i++)
        {
            for (int j = 0; j < arg.cols(); j++)
            {
                out[i][0] += arg[i][j];
            }
        }

    } else if (axis == 0)
    {
        out = zeros<T>({1, arg.cols()});
        for (int i = 0; i < arg.rows(); i++)
        {
            for (int j = 0; j < arg.cols(); j++)
            {
                out[0][j] += arg[i][j];
            }
        }
    }

    return out;

}

#endif