#include <time.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

// #include "matplotlibcpp.h"

// To save std::
using namespace std;
// OR
using std::cout;
using std::endl;

// namespace plt = matplotlibcpp;

// find the longest repeats within a list and its position
template <typename T>
tuple<int, int, int> longest_repeat(vector<T> V) {
    int n = V.size();
    int max_length = 1;
    int start = 0;
    int end = 0;
    int curr_length = 0;
    T ref = V[0];
    for (int i = 0; i < n; i++) {
        if (V[i] == ref) {
            curr_length = curr_length + 1;
            if (curr_length > max_length) {
                max_length = curr_length;
                end = i;
                start = end - max_length + 1;
            }
        } else {
            curr_length = 1;
            ref = V[i];
        }
    }

    tuple<int, int, int> res(max_length, start, end);
    return res;
}

// find the length of the longest the consecutive 1s in a binary sequence
// also the position
tuple<int, int, int> longest_repeat_bin(vector<int> V) {
    int n = V.size();
    int max_length = 1;
    int start = 0;
    int end = 0;
    int curr_length = 0;
    for (int i = 0; i < n; i++) {
        if (V[i] == 1) {
            curr_length = curr_length + 1;
            if (curr_length > max_length) {
                max_length = curr_length;
                end = i;
                start = end - max_length + 1;
            }
        } else {
            // if (curr_length > max_length) {
            //     max_length = curr_length;
            //     end = i - 1;
            //     start = end - max_length + 1;
            // }
            curr_length = 0;
        }
    }

    tuple<int, int, int> res(max_length, start, end);
    return res;
}

int main() {
    // wall time
    auto start = chrono::high_resolution_clock::now();

    // std::minstd_rand gen(12345);
    std::random_device rd;
    std::mt19937_64 gen(rd());

    // (1) limsup Xn / log(n) = 1, A.S., Xn ~ Exp(1);
    // (2) limsup Mn / log(n) = 1, A.S., Mn:= max{Xj : j <= n}
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
    // plt::plot(r_Xn_logn);
    // plt::plot(ref, "r.--");
    // plt::title("limsup Xn / log n");
    // plt::show();

    // plt::plot(r_Mn_logn);
    // plt::plot(ref, "r.--");
    // plt::title("limsup Mn / log n");
    // plt::show();

    // Rn:= the longest consecutive run of 1s in a binary string of length n
    // (3) lim Rn / (log(n)/log(2)) = 1 A.S.
    std::bernoulli_distribution ber(0.5);
    int n = 1000000;
    vector<int> V;
    for (int i = 0; i < n; i++) {
        bool b = ber(gen);
        if (b) {
            V.push_back(1);
        } else {
            V.push_back(0);
        }
    }
    tuple<int, int, int> t = longest_repeat_bin(V);
    // cout << count << endl;
    // cout << count * 1.0 / (log(n) / log(2)) << endl;
    cout << "length: " << get<0>(t) << endl;
    cout << "position: " << get<1>(t) << " " << get<2>(t) << endl;
    cout << "ratio: " << get<0>(t) * 1.0 / (log(n) / log(2)) << endl;

    // vector<string> V2{"A", "B", "A", "A", "A", "B", "B", "C", "D", "D", "D", "D"};
    // tuple<int, int, int> t2 = longest_repeat(V2);
    // cout << get<0>(t2) << " " << get<1>(t2) << " " << get<2>(t2) << endl;

    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

    return 0;
}