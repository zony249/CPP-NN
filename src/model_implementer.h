#ifndef MODEL_IMPLEMENTER_H
#define MODEL_IMPLEMENTER_H

void linker_helper3 ()
{
    Model<float> A(1e-2, 0.0);
    Model<double> B(1e-2, 0.0);
    Model<float> C;
    Model<double> D;
    Layer<float> l1(5, "relu");
    Layer<double> l2(10, "relu");
    C.add_layer(l1);
    D.add_layer(l2);
    cout << C << endl;
    cout << D << endl;

}

#endif