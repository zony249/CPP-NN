#include <iostream>
#include <string>
#include "matrix.h"

using namespace std;

int main(int argc, char* argv[])
{
    Matrix<float> A(3, 3, 3.14159);
    cout << "A: " << endl;
    cout << A << endl;

    Matrix<float> B(4, 4, 4.0);
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

    Matrix<float> E(3, 3, 2);
    Matrix<float> F(3, 3, 3);
    Matrix<float> G(3, 3, 4);
    Matrix<float> H(3, 3, 5);

    H = H + G - F - E;
    cout << "H = H + G - F - E: " << endl;
    cout << H << endl;

    return 0;
}