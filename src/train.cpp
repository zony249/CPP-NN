#include <iostream>
#include <string>
#include "matrix.h"

using namespace std;

int main(int argc, char* argv[])
{
    Matrix<float> A({3, 3}, 3.14159);
    cout << "A: " << endl;
    cout << A << endl;

    Matrix<float> B({4, 4}, 4.0);
    cout << "B: " << endl;
    cout << B << endl;

    B = A;
    cout << "B = A: " << endl;
    cout << B << endl;

    Matrix<float> C = B;
    cout << "Matrix C = B: " << endl;
    cout << C << endl;

    Matrix<float> D = B + C;
    cout << "D = B + C: " << endl;
    cout << D << endl;

    Matrix<float> E({3, 3}, 2);
    Matrix<float> F({3, 3}, 3);
    Matrix<float> G({3, 3}, 4);
    Matrix<float> H({3, 3}, 5);

    H = H + G - F - E;
    cout << "H = H + G - F - E: " << endl;
    cout << H << endl;

    H[0][0] = 5;
    cout << H << endl;
    H = H*H;

    cout << "H*H: " << endl;
    cout << H << endl;

    Matrix<float> J({4, 4}, 5);
    Matrix<float> K({4, 4}, 2);

    J = (J/K)/2 + 3;

    cout << "This should be 4.25" << endl;
    cout << J << endl;

    const Matrix<float> L({5, 5}, 9);
    cout << "testing const [] operator: " << endl;
    cout << L[0][0] << endl;
    // L[0][1] = 6; crashes compiler

    cout << L.rows() << " " << L.cols() << " " << L.size() << " " << L.shape()[0] << " " << L.shape()[1] << endl;

    Matrix<float> M({3, 4}, 5);
    cout << "M: " << endl;
    cout << M << endl;
    cout << "M.tp()" << endl;
    cout << M.tp() << endl;

    cout << "M.flatten(): " << endl;
    cout << M.flatten() << endl;
    cout << M.flatten().shape()[0] << ", " << M.flatten().shape()[1] << endl;

    cout << M.flatten().tp() << endl;
    cout << M.flatten().tp().shape()[0] << ", " << M.flatten().tp().shape()[1] << endl;

    cout << "H: " << endl;
    cout << H << endl;

    cout << "H[0]: " << endl;
    cout << H.get_row(0) << endl;

    Matrix<float> N({3, 3}, 0);
    cout << "N before row insertion: " << endl;
    cout << N << endl;
    cout << "N after row insertion at row [1]: " << endl;
    
    cout << N.set_row(1, H.get_row(0)) << endl;
    cout << N << endl;
    N = N.set_row(1, H.get_row(0));
    cout << N << endl;
    
    Matrix<float> O({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    O = O.reshape({4, 4});
    cout << "O: " << endl;
    cout << O << endl;

    Matrix<float> P = Id<float> ({4, 4});
    cout << "Identity: " << endl;
    cout << P << endl;

    Matrix<float> Q({7, 8, 0, 6, 5, 8, 6, 5, 3});
    Q = Q.reshape({3, 3});
    cout << "Q: " << endl;
    cout << Q << endl;
    cout << "Q.inv(): " << endl;
    cout << Q.inv() << endl;


    {Matrix<float> R({100000, 100000}, 0);}
    string x;
    cin >> x;
    return 0;
}