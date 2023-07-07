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
    // std::minstd_rand gen(12345);
    // std::default_random_engine gen;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // number of steps
    int n = 100000;

    // 1_D case:
    double prob = 0.5;
    std::bernoulli_distribution ber(prob);

    int X_i = 0;
    vector<int> X = {X_i};
    vector<int> time = {0};

    for (int i = 1; i <= n; i++) {
        bool b = ber(gen);
        int Z_i;
        if (!b) {
            Z_i = -1;
        } else {
            Z_i = 1;
        }
        X_i = X_i + Z_i;
        X.push_back(X_i);
        time.push_back(i);
    }

    plt::plot(X);
    plt::show();

    // 2-D case
    int Xi = 0;
    int Yi = 0;
    vector<int> Xs = {Xi};
    vector<int> Ys = {Yi};

    std::uniform_int_distribution<> unif(0, 3);

    // if we use cts unif dist, then dir = 0 when 0 <= dir < 0.25; dir = 1 when 0.25 <= dir < 0.5...

    for (int i = 1; i <= n; i++) {
        int dir = unif(gen);
        int dXi = (int)cos((M_PI / 2) * dir);
        int dYi = (int)sin((M_PI / 2) * dir);

        Xi = Xi + dXi;
        Yi = Yi + dYi;
        Xs.push_back(Xi);
        Ys.push_back(Yi);
    }

    plt::plot(Xs, Ys);
    plt::title("2D SRW without time progress");
    plt::show();

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}