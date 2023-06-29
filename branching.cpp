#include <time.h>

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

#include "SBM.cpp"
#include "matplotlibcpp.h"

// To save std::
using namespace std;
// OR
using std::cout;
using std::endl;

namespace plt = matplotlibcpp;

int main() {
    // wall time
    auto start = chrono::high_resolution_clock::now();

    // std::random_device rd;
    // std::mt19937_64 gen(rd());
    // std::minstd_rand gen(12345);
    // std::default_random_engine gen;

    int n = 20;

    // mu < 1, Zn = 0 a.s.
    // mu > 1, 0 < P(Zn = 0 for some n) < 1
    // mu = 1, if P(X = 1) = 1, then P(Zn = 0) = 0; if P(X = 1) < 1, then P(Zn = 0) = 1
    double mu = 0.999;

    // X has dist: P(X = k) = pk, k in {0,1,2,...}
    // Some choices for pmf of X: poisson, binomial or user-defined pmf
    // std::minstd_rand gen(12345);
    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::poisson_distribution<> pois(1);
    double p = mu / n;
    std::binomial_distribution<> binom(n, p);

    vector<int> Z;
    int prev_generation = 1;

    vector<double> Y;

    for (int i = 1; i <= n; i++) {
        int curr_generation = 0;
        for (int j = 1; j <= prev_generation; j++) {
            // int X = pois(gen);
            int X = binom(gen);
            curr_generation = curr_generation + X;
        }
        int Zi = curr_generation;
        Z.push_back(Zi);
        cout << "Zi: " << Zi << endl;
        double Yi = (Zi * 1.0) / pow(mu, i);
        // {Zi / mu^n} is martingale
        Y.push_back(Yi);
        prev_generation = Zi;
        // if (prev_generation == 0) {
        //     break;
        // }
    }

    plt::plot(Z, ".-");
    plt::legend();
    plt::plot(Y, "r.-");
    plt::legend();
    plt::show();

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;
    return 0;
}