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

class mvrnormal {
   public:
    VectorXd mean;
    int d;  // dimension
    // matrix S = diag(sqrt(lambda)), such that SIGMA = S * S^T
    // T = [eigenvectors] * S
    MatrixXd T;

    // constructor
    mvrnormal(const VectorXd* MU, const MatrixXd* SIGMA) {
        this->mean = *MU;
        d = (*MU).size();

        // initialize eigenspace
        EigenSolver<MatrixXd> es(*SIGMA);
        MatrixXd evec = es.eigenvectors().real();
        MatrixXd eval = es.eigenvalues().real();

        // construct S and T
        MatrixXd S(d, d);
        for (int i = 0; i < d; i++) {
            for (int j = 0; j < d; j++) {
                if (i == j) {
                    S(i, j) = sqrt(eval(i, 0));
                } else {
                    S(i, j) = 0;
                }
            }
        }
        this->T = evec * S;
    }

    VectorXd operator()() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());

        std::normal_distribution<> N(0, 1);
        VectorXd Z(d);
        for (int i = 0; i < d; i++) {
            Z(i) = N(gen);
        }
        return mean + T * Z;
    }
};

struct normal_random_variable {
    normal_random_variable(MatrixXd const& covar)
        : normal_random_variable(VectorXd::Zero(covar.rows()), covar) {}

    normal_random_variable(VectorXd const& mean, MatrixXd const& covar)
        : mean(mean) {
        SelfAdjointEigenSolver<MatrixXd> eigenSolver(covar);
        transform = eigenSolver.eigenvectors() * eigenSolver.eigenvalues().cwiseSqrt().asDiagonal();
    }

    VectorXd mean;
    MatrixXd transform;

    VectorXd operator()() const {
        static std::mt19937 gen{std::random_device{}()};
        static std::normal_distribution<> dist;

        return mean + transform * VectorXd{mean.size()}.unaryExpr([&](auto x) { return dist(gen); });
    }
};

// MatrixXd mvrnormal(int n, const VectorXd *MU, const MatrixXd *Sigma) {
//     int p = (*MU).size();

//     // std::minstd_rand gen(12345);
//     std::normal_distribution<> N(0, 1);

//     MatrixXd X(p, n);
//     for (int i = 0; i < p; i++) {
//         std::random_device rd;
//         std::mt19937_64 gen(rd());
//         for (int j = 0; j < n; j++) {
//             X(i, j) = N(gen);
//         }
//     }

//     // initialize eigenspace
//     EigenSolver<MatrixXd> es(*Sigma);

//     MatrixXd evec = es.eigenvectors().real();
//     MatrixXd eval = es.eigenvalues().real();

//     // construct matrix S = diag(sqrt(lambda)), such that Sigma = S * S^T
//     // D = eval.asDiagonal();
//     MatrixXd S(p, p);
//     for (int i = 0; i < p; i++) {
//         for (int j = 0; j < p; j++) {
//             if (i == j) {
//                 S(i, j) = sqrt(eval(i, 0));
//             } else {
//                 S(i, j) = 0;
//             }
//         }
//     }

//     MatrixXd MU_copy(p, n);
//     for (int i = 0; i < p; i++) {
//         for (int j = 0; j < n; j++) {
//             MU_copy(i, j) = (*MU)(i);
//         }
//     }

//     X = MU_copy + evec * S * X;

//     return X;
// }

// int main() {
//     // auto start = chrono::high_resolution_clock::now();

//     VectorXd MU(2);
//     MU(0) = 0;
//     MU(1) = 0;
//     MatrixXd Sigma(2, 2);
//     Sigma(0, 0) = 1;
//     Sigma(0, 1) = 0;
//     Sigma(1, 0) = 0;
//     Sigma(1, 1) = 1;

//     MatrixXd X = mvrnormal(1, &MU, &Sigma);

//     // cout << MU << endl;
//     // cout << Sigma << endl;
//     cout << X << endl;
//     cout << X(0, 0) << endl;
//     cout << X(1, 0) << endl;
//     // auto end = chrono::high_resolution_clock::now();
//     // auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - start);
//     // cout << "Time taken: " << timeTaken.count() << " milliseconds" << endl;

//     return 0;
// }
