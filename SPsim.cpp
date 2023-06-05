#include <time.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
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
    // auto start = chrono::high_resolution_clock::now();

    vector<double> X;
    vector<double> Y;

    for (double i = 0; i < 7; i+=0.01) {
        X.push_back(i);
        Y.push_back(sin(i));
    }


    plt::plot(X,Y);
    plt::show();


    // auto end = chrono::high_resolution_clock::now();

    // double timeTaken = (end - start) / CLOCKS_PER_SEC;
    // auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    // cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}