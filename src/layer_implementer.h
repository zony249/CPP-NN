#ifndef LAYER_IMPLEMENTER
#define LAYER_IMPLEMENTER

void linker_helper2()
{
    Layer<float> A(1, "x");
    Layer<double> B(1, "x");
    A.size();
    B.size();
    cout << A << endl;
    cout << B << endl;

}

#endif