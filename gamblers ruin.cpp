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

// return a process of gambler's current fortune
vector<int> gamblersRuin(int goal, int start, double p, int seed) {
    std::minstd_rand gen(seed);
    std::bernoulli_distribution ber(p);
    int X_i = start;
    vector<int> X;
    X.push_back(X_i);
    int i = 1;
    // stopping time tau = min{T0, TN}, where T0 = inf{t > 0 : Xt = 0}; TN = inf{t > 0 : Xt = N}
    while (X_i != 0 && X_i != goal) {
        bool b = ber(gen);
        int Z_i;
        if (!b) {
            Z_i = -1;
        } else {
            Z_i = 1;
        }
        X_i = X_i + Z_i;
        X.push_back(X_i);
        i = i + 1;
    }

    return X;
}

int main() {
    // wall time
    auto start = chrono::high_resolution_clock::now();
    double p = 0.5;

    // std::random_device gen;
    // std::minstd_rand gen(12345);
    // std::default_random_engine gen;

    // std::bernoulli_distribution ber(p);

    int goal = 100;
    int X0 = 10;
    // plot a gamber's ruin process
    vector<int> gr = gamblersRuin(goal, X0, p, 123);
    plt::plot(gr);
    plt::show();

    // compute the probability of ruin
    int N = 100;
    int ruin = 0;

    for (int i = 1; i <= N; i++) {
        vector<int> X = gamblersRuin(goal, X0, p, i);
        // stopping time: tau
        int tau = X.size() - 1;
        cout << X[tau] << endl;
        if (X[tau] == 0) {
            ruin = ruin + 1;
        }
    }

    cout << "ruin probability: " << ruin * 1.0 / N << endl;

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}