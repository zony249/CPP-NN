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
    C.connect();
    D.connect();
    Matrix<float> M;
    Matrix<double> N;
    vector<pair<Matrix<float>, Matrix<float> > > fset;
    vector<pair<Matrix<double>, Matrix<double> > > dset;
    C.load_training_data(&fset);
    C.load_cv_data(&fset);
    D.load_training_data(&dset);
    D.load_cv_data(&dset);

    C.train(16);
    D.train(16);
    vector<Layer<float> > f;
    vector<Layer<double> > d;
    float lf;
    double ld;
    C.train_thread(16, 14, f, lf);
    D.train_thread(16, 14, d, ld);
    C.forward_prop(M, f);
    D.forward_prop(N, d);
    C.back_prop(M, f);
    D.back_prop(N, d);
    C.predict(M);
    D.predict(N);
    C.evaluate();
    D.evaluate();
}

#endif