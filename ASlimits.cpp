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
    std::minstd_rand gen(12345);
    std::exponential_distribution<> Exp(1);

    int n = 100000;
    vector<double> X;
    vector<double> r_Xn_logn;
    vector<double> r_Mn_logn;
    vector<double> ref;
    double M = -1;

    for (int i = 1; i <= n; i++) {

        double Xi = Exp(gen);
        X.push_back(Xi);
        r_Xn_logn.push_back(Xi / log(i));

        // get max{Xj : 1 <= j <= i}
        if (Xi > M) {
            M = Xi;
        }
        r_Mn_logn.push_back(M / log(i));

        ref.push_back(1);
    }

    plt::plot(r_Xn_logn);
    plt::plot(ref, "r.--");
    plt::title("lim_n Xn / log n");
    plt::show();

    plt::plot(r_Mn_logn);
    plt::plot(ref, "r.--");
    plt::title("lim_n Mn / log n");
    plt::show();

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}