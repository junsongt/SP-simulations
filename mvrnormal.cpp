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

// To save std::
using namespace std;
using namespace Eigen;
// OR
using std::cout;
using std::endl;

MatrixXd mvrnormal(int n, const VectorXd *MU, const MatrixXd *Sigma) {
    int p = (*MU).size();

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<> N(0, 1);

    MatrixXd X(p, n);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n; j++) {
            X(i, j) = N(gen);
        }
    }

    // initialize eigenspace
    EigenSolver<MatrixXd> es(*Sigma);

    MatrixXd evec = es.eigenvectors().real();
    MatrixXd eval = es.eigenvalues().real();

    // construct matrix S = diag(sqrt(lambda)), such that Sigma = S * S^T
    // D = eval.asDiagonal();
    MatrixXd S(p, p);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            if (i == j) {
                S(i, j) = sqrt(eval(i, 0));
            } else {
                S(i, j) = 0;
            }
        }
    }

    MatrixXd MU_copy(p, n);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n; j++) {
            MU_copy(i, j) = (*MU)(i);
        }
    }

    X = MU_copy + evec * S * X;

    return X;
}

// int main() {
//     // auto start = chrono::high_resolution_clock::now();

//     // VectorXd MU(2);
//     // MU(0) = 1;
//     // MU(1) = 2;
//     // MatrixXd Sigma(2, 2);
//     // Sigma(0, 0) = 2;
//     // Sigma(0, 1) = 0;
//     // Sigma(1, 0) = 0;
//     // Sigma(1, 1) = 3;

//     // MatrixXd X = mvrnormal(10, &MU, &Sigma);

//     // // cout << MU << endl;
//     // // cout << Sigma << endl;
//     // cout << X << endl;
//     // auto end = chrono::high_resolution_clock::now();
//     // auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
//     // cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

//     return 0;
// }
