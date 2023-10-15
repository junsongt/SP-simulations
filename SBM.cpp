#include <time.h>

#include <Eigen/Dense>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>

#include "matplotlibcpp.h"
#include "mvrnormal.cpp"

// To save std::
using namespace std;
// OR
using std::cout;
using std::endl;

namespace plt = matplotlibcpp;

template <typename T>
vector<T> seq(T from, T to, T by) {
    T curr = from;
    vector<T> X;
    while (curr <= to) {
        X.push_back(curr);
        curr = curr + by;
    }
    return (X);

    // int N = (to - from) / by;
    // vector<T> X;
    // for (int i = 0; i <= N; i++) {
    //     T curr = from + i * by;
    //     X.push_back(curr);
    // }
    // return (X)
}



// Standard Brownian Motion(Levy construction);
// param: B0, B1, partition of time[0,1], random seed
pair<vector<double>, vector<double>> SBM(double startpt, double endpt, int n) {
    vector<double> prev_B{startpt, endpt};
    vector<double> time;
    vector<double> pos;

    // std::minstd_rand gen(seed);

    std::random_device rd;
    std::mt19937_64 gen(rd());

    for (int i = 1; i <= n; i++) {
        // Dyadic rationals: Dn = {k/2^n : 0 <= k <= 2^n}, length 2^n
        vector<double> D_i = seq(0.0, 1.0, (1.0 / pow(2, i)));
        vector<double> curr_B;

        for (int j = 0; j < D_i.size(); j++) {
            // j even
            if (j % 2 == 0) {
                curr_B.push_back(prev_B[j / 2]);
            } else {
                std::normal_distribution<> N(0, sqrt(j / pow(2, i)));
                double Z_j = N(gen);
                curr_B.push_back(0.5 * (prev_B[(j - 1) / 2] + prev_B[(j + 1) / 2]) + pow(0.5, (i + 1.0) / 2) * Z_j);
            }
        }
        prev_B = curr_B;

        time = D_i;
        pos = curr_B;
    }
    pair<vector<double>, vector<double>> sbm(time, pos);
    return sbm;
}

// 2D standard brownian motion
// pair<vector<double>, vector<pair<double, double>>>
tuple<vector<double>, vector<double>, vector<double>> SBM_2D(pair<double, double> startpt, pair<double, double> endpt, int n) {
    // std::random_device rd;
    // std::mt19937_64 gen(rd());

    // vector<double> time;
    vector<double> prev_Bx{startpt.first, endpt.first};
    vector<double> prev_By{startpt.second, endpt.second};

    vector<double> Bx;
    vector<double> By;

    VectorXd MU(2);
    MU(0) = 0;
    MU(1) = 0;
    MatrixXd SIGMA(2, 2);

    vector<double> D_i;

    for (int i = 1; i <= n; i++) {
        // Dyadic rationals: Dn = {k/2^n : 0 <= k <= 2^n}, length 2^n
        D_i = seq(0.0, 1.0, (1.0 / pow(2, i)));
        vector<double> curr_Bx;
        vector<double> curr_By;

        for (int j = 0; j < D_i.size(); j++) {
            // j even
            if (j % 2 == 0) {
                curr_Bx.push_back(prev_Bx[j / 2]);
                curr_By.push_back(prev_By[j / 2]);
            } else {
                SIGMA(0, 0) = (j * 1.0) / pow(2, i);
                SIGMA(0, 1) = 0;
                SIGMA(1, 0) = 0;
                SIGMA(1, 1) = (j * 1.0) / pow(2, i);

                // normal_random_variable MVN{SIGMA};
                // VectorXd Z_j = MVN();

                mvrnormal MVN(&MU, &SIGMA);
                VectorXd Z_j = MVN();

                curr_Bx.push_back(0.5 * (prev_Bx[(j - 1) / 2] + prev_Bx[(j + 1) / 2]) + pow(0.5, (i + 1.0) / 2) * Z_j(0));
                curr_By.push_back(0.5 * (prev_By[(j - 1) / 2] + prev_By[(j + 1) / 2]) + pow(0.5, (i + 1.0) / 2) * Z_j(1));
            }
        }
        prev_Bx = curr_Bx;
        prev_By = curr_By;

        // time = D_i;
        Bx = curr_Bx;
        By = curr_By;
    }

    tuple<vector<double>, vector<double>, vector<double>> sbm_2d(D_i, Bx, By);
    return sbm_2d;
}

// int main() {
//     // wall time
//     auto start = chrono::high_resolution_clock::now();

//     // std::random_device rd;
//     // std::mt19937_64 gen(rd());
//     // std::minstd_rand gen(12345);
//     // std::default_random_engine gen;
//     std::minstd_rand gen(123);
//     std::uniform_real_distribution<> U(0, 1);
//     double endpt = U(gen);

//     pair<vector<double>, vector<double>> B = SBM(0, endpt, 10, 321);
//     plt::plot(B.first, B.second);
//     plt::show();

//     auto end = chrono::high_resolution_clock::now();
//     auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

//     return 0;
// }