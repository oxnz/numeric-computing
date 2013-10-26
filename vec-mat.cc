#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

namespace Vec {
    const int maxsize = 100000;
    double onenorm(const double* const, int); // 1 norm
    double twonorm(const double* const, int);
    double maxnorm(const double* const, int); // infinite norm
}
namespace Mat {
    double onenorm(const double** const, int); // 1 norm
    double twonorm(const double** const, int);
    double maxnorm(const double** const, int); // infinite norm
}

double Vec::onenorm(const double* const v, int size) {
    if (size > maxsize) cout << "Vector size too large" << endl;
    double norm = fabs(v[0]);
    for (int i = 1; i < size; ++i)
        norm += fabs(v[i]);
    return norm;
}

double Vec::twonorm(const double* const v, int size) {
    if (size > maxsize) cout << "Vector size too large" << endl;
    double norm = v[0]*v[0];
    for (int i = 1; i < size; ++i) 
        norm += v[i]*v[i]; 
    return sqrt(norm);
}

double Vec::maxnorm(const double* const v, int size) {
    if (size > maxsize) cout << "Vector size too large" << endl;
    double norm = fabs(v[0]);
    for (int i = 0; i < size; ++i)
        norm = fmax(norm, fabs(v[i]));
    return norm;
}

double Mat::maxnorm(const double** const m, int size) {
    double norm = Vec::onenorm(m[0], size);
    for (int i = 1; i < size; ++i)
        norm = fmax(norm, Vec::onenorm(m[i], size));
    return norm;
}

double Mat::onenorm(const double** const m, int size) {
    double norm = 0;
    for (int i = 0; i < size; ++i) {
        double tmp = 0;
        for (int j = 0; j < size; ++j)
            tmp += fabs(m[j][i]);
        norm = fmax(norm, tmp);
    }
    return norm;
}

double Mat::twonorm(const double** const m, int size) {
    double norm = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            norm += m[i][j]*m[i][j];
    return sqrt(norm);
}

int main() {
    int n = 1000;
    double** const m = new double* [n];
    for (int i = 0; i < n; ++i)
        m[i] = new double [n];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            m[i][j] = 1.0/(i+j+1);
    cout << Mat::maxnorm((const double**)m, n) << endl
         << Vec::maxnorm(m[2], n) << endl;
    return 0;
}
