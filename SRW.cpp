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
    double p = 0.5;

    std::random_device gen;
    // std::minstd_rand gen(12345);
    // std::default_random_engine gen;

    std::bernoulli_distribution ber(p);

    int n = 100000;
    int X_i = 0;
    vector<int> X;

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
    }

    plt::plot(X);
    plt::show();

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}