#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <thread>
#include "matrix.h"


using namespace std;


template <class T> vector<pair<Matrix<T>, Matrix<T> > > read_MNIST_csv(string);
template <class T> void parse_MNIST_line(vector<string>&, int, int, vector<pair<Matrix<T>, Matrix<T> > >&);

// template <class T> pair<Matrix<T>, Matrix<T> > read_MNIST_csv(string filename);

// template <class T>
// pair<Matrix<T>, Matrix<T> > read_MNIST_csv(string filename)
// {
//     Matrix<T> X;
//     Matrix<T> Y;
//     FILE* input = fopen(filename.c_str(), "r");
//     if (!input)
//         throw runtime_error("Failed to open " + filename);

//     string line;
//     bool ignore_first = true;
//     vector<T> Yv;
//     vector<Matrix<T> > Xrow_to_X;
//     int linenum = 0;
//     bool skip_fields = true;

//     char x;
//     while (x != EOF)
//     {
//         vector<T> Xrowv;        
//         //cout << "Reading CSV Line " << linenum++ << endl;
        
//         int j = 0;
        
//         char buffer[8];
//         bool is_class = true;
        
//         while((x = fgetc(input)) != EOF)
//         {
//             if (x == ',')
//             {
                
//                 buffer[j] = '\0';
//                 j = 0;
//                 if (!skip_fields)
//                 {
//                     if (is_class)Yv.push_back((T)atof(buffer));
//                     else Xrowv.push_back((T)atof(buffer));
//                 }
//                 is_class = false;
//                 continue;
//             } else if (x == '\n')
//             {
//                 buffer[j] = '\0';
//                 j = 0;
//                 if (!skip_fields)
//                 {
//                     Xrowv.push_back((T)atof(buffer));
//                 }
//                 break;
//             }
//             buffer[j] = x;
//             j++;
//         }
//         skip_fields = false;

//         if (Xrowv.size() > 0)
//         {
//             Matrix<T> Xrow(Xrowv);
//             Xrow_to_X.push_back(Xrow.tp());
//         }
//     }
//     Y = Matrix<T>(Yv).tp();
//     X = Matrix<T>({(unsigned int)Xrow_to_X.size(), Xrow_to_X[0].size()}, 0);
//     //cout << (unsigned int)Xrow_to_X.size() << ", "  << Xrow_to_X[0].size() << endl;
//     for (int i = 0; i < Xrow_to_X.size(); i++)
//     {
//         //cout << Xrow_to_X[i].cols() << ", " <<  i << endl;
//         X.set_row(i, Xrow_to_X[i]);
//     }
//     X = X.tp();
    
//     pair<Matrix<T>, Matrix<T> > dataset = {X, Y};
//     return dataset;
// }


template <class T>
vector<pair<Matrix<T>, Matrix<T> > > read_MNIST_csv(string filename)
{
    int n_threads = 8;
    cout << "Reading " << filename << "..." << endl;
    cout << "Number of threads: " << n_threads << endl;


    ifstream infile(filename);
    if (!infile.good())
        throw runtime_error("Cannot open file " + filename);

    string line;
    vector<string> all_lines;
    vector<vector<pair<Matrix<T>, Matrix<T> > > > parsed_data_disjoint;
    
    bool skip_first = true;
    while (getline(infile, line))
    {
        if (skip_first)
        {
            skip_first = false;
            continue;
        }
        all_lines.push_back(line);
    }

    vector<thread> processes;
    int start = 0;
    int end = 0;
    for (int i = 0; i < n_threads; i++)
    {
        vector<pair<Matrix<T>, T> > slice;
        parsed_data_disjoint.push_back({});
    }
    for (int i = 0; i < n_threads; i++)
    {
        end = start + all_lines.size()/n_threads;
        if (i == n_threads-1) end = all_lines.size();
        //cout << start << ", " << end << endl;
        processes.push_back(thread(parse_MNIST_line<T>, ref(all_lines), start, end,  ref(parsed_data_disjoint[i])));
        start = end;
    }

    for (int i = 0; i < n_threads; i++)processes[i].join();

    vector<pair<Matrix<T>, Matrix<T> > > parsed_data;
    for (int i = 0; i < n_threads; i++)
    {
        parsed_data.insert(parsed_data.end(), parsed_data_disjoint[i].begin(), parsed_data_disjoint[i].end());
    }
    
    return parsed_data;
}

template <class T>
void parse_MNIST_line(vector<string>& lines, int start, int end, vector<pair<Matrix<T>, Matrix<T> > > & parsed_data)
{
    
    for (int i = start; i < end; i++)
    {
        vector<T> xrowv;
        Matrix<T> y;
        int k = 0;
        char buffer[8];
        bool first = true;
        for (int j = 0; j < lines[i].size(); j++)
        {
            char x = lines[i][j];
            if (x == ',')
            {
                buffer[k] = '\0';
                
                if (first)      
                {
                    first = false;
                    y = Matrix<T>({1, 10}, 0);
                    int index = (int)atof(buffer);
                    y[0][index] = 1;
                    continue;
                }
                xrowv.push_back((T)atof(buffer));
                k = 0;
                continue;
            }
            buffer[k] = x;
            k++;
        }

        buffer[k] = '\0';
        xrowv.push_back((T)atof(buffer));

        Matrix<T> x(xrowv);
        pair<Matrix<T>, Matrix<T> > datapoint = {x, y};
        parsed_data.push_back(datapoint);

    }

}

#endif