#ifndef MATRIX_IMPLEMENTER
#define MATRIX_IMPLEMENTER

/* 
Implementations of template class Matrix<T>
basically a shitty way of saying "HEY LINKER, THIS
WAY OF IMPLEMENTING EXISTS"
*/
void link_helper()
{
    Matrix<float> P;
    Matrix<int> Q;
    Matrix<double> R;
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
    Matrix<float> X = helperFloat.dot(helperFloat);
    Matrix<double> Y = helperDoub.dot(helperDoub);
    Matrix<int> Z = helperInt.dot(helperInt);
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
    A = (float)1 + A;
    B = (float)1 + B;
    C = (float)1 + C;
    A = (double)1 + A;
    B = (double)1 + B;
    C = (double)1 + C;
    A = (int)1 + A;
    B = (int)1 + B;
    C = (int)1 + C;
    A = (float)1 - A;
    B = (float)1 - B;
    C = (float)1 - C;
    A = (double)1 - A;
    B = (double)1 - B;
    C = (double)1 - C;
    A = (int)1 - A;
    B = (int)1 - B;
    C = (int)1 - C;
    A = (float)1 * A;
    B = (float)1 * B;
    C = (float)1 * C;
    A = (double)1 * A;
    B = (double)1 * B;
    C = (double)1 * C;
    A = (int)1 * A;
    B = (int)1 * B;
    C = (int)1 * C;
    A = (float)1 / A;
    B = (float)1 / B;
    C = (float)1 / C;
    A = (double)1 / A;
    B = (double)1 / B;
    C = (double)1 / C;
    A = (int)1 / A;
    B = (int)1 / B;
    C = (int)1 / C;
}


#endif

