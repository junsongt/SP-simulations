#include <time.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>

#include "SBM.cpp"
#include "matplotlibcpp.h"

// To save std::
using namespace std;
// OR
using std::cout;
using std::endl;

namespace plt = matplotlibcpp;

// Browian bridge
// Xt = a*t + (Bt - t*B1), t in [0,1]; a is the fixed endpt
pair<vector<double>, vector<double>> brownian_bridge(double B0, double B1, int n, double endpt, int seed) {
    pair<vector<double>, vector<double>> sbm = SBM(B0, B1, n);
    vector<double> time = sbm.first;
    vector<double> pos = sbm.second;

    // double B1 = pos[time.size()-1];

    vector<double> X;
    for (int i = 0; i < time.size(); i++) {
        double t = time[i];
        double Bt = pos[i];
        X.push_back(endpt * t + Bt - t * B1);
    }
    return pair<vector<double>, vector<double>>{time, X};
}

// Geometric brownian motion
pair<vector<double>, vector<double>> GBM(double mu, double sigma, int n, int seed) {
    std::minstd_rand gen(seed);
    std::normal_distribution<> N(0, 1);
    double B1 = N(gen);

    pair<vector<double>, vector<double>> sbm = SBM(0, B1, n);
    vector<double> time = sbm.first;
    vector<double> Bt = sbm.second;

    vector<double> X;
    for (int i = 0; i < time.size(); i++) {
        double t = time[i];
        X.push_back(exp((mu - (pow(sigma, 2) / 2)) * t + sigma * Bt[i]));
    }
    return pair<vector<double>, vector<double>>{time, X};
}

int main() {
    // wall time
    auto start = chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    // std::minstd_rand gen(12345);
    // std::default_random_engine gen;

    // 1D SBM
    double b0 = 0;
    // std::uniform_real_distribution<> U(0, 1);
    std::normal_distribution<> N(0, 1);
    double b1 = N(gen);

    pair<vector<double>, vector<double>> B = SBM(b0, b1, 15);
    plt::plot(B.first, B.second);
    plt::title("standard browian motion");
    plt::show();

    // 2D SBM
    VectorXd MU(2);
    MU(0) = 0;
    MU(1) = 0;
    MatrixXd SIGMA(2, 2);
    SIGMA(0, 0) = 1;
    SIGMA(0, 1) = 0;
    SIGMA(1, 0) = 0;
    SIGMA(1, 1) = 1;
    pair<double, double> B0{0, 0};

    mvrnormal MVN(&MU, &SIGMA);
    VectorXd Z = MVN();
    // pair<double, double> B1{temp(0, 0), temp(1, 0)};

    pair<double, double> B1{Z(0), Z(1)};

    tuple<vector<double>, vector<double>, vector<double>> B_2d = SBM_2D(B0, B1, 15);

    // save data into file
    ofstream dataframe("./data files/sbm.txt");
    cout << "Start writing data file..." << endl;
    dataframe << "time"
              << ","
              << "X_1D"
              << ","
              << "X_2D"
              << ","
              << "Y_2D" << endl;
    for (int i = 0; i < B.first.size(); i++) {
        dataframe << B.first[i] << "," << B.second[i] << "," << get<1>(B_2d)[i] << "," << get<2>(B_2d)[i] << endl;
    }
    dataframe.close();

    cout << "Finish writing data file!" << endl;

    // // generate brownian bridge with fixed endpt -0.5
    // pair<vector<double>, vector<double>> Bb = brownian_bridge(B0, B1, 10, -0.5, 321);
    // plt::plot(Bb.first, Bb.second);
    // plt::title("brownian bridge with fixed endpt -0.5");
    // plt::show();

    // // generate GBMs with mu=1, different sd:(1,1.5.2,2.5,3,3.5,4)
    // for (int i = 0; i <= 5; i++) {
    //     pair<vector<double>, vector<double>> gbm = GBM(1, 1 + i * 0.5, 10, 123);
    //     plt::plot(gbm.first, gbm.second);
    // }
    // plt::title("geometric browian motion");
    // plt::legend();
    // plt::show();

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;
    return 0;
}