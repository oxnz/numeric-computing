#include <iostream>
#include <cmath>
#include "vtr.h"

using namespace std;

class Mtx {
private:
    int nrows;
    int ncols;
    double** ets; // elements
public:
    Mtx(int n, int m, double**);
    Mtx(int n, int m, double d = 0);
    Mtx(const Mtx&);
    ~Mtx();

    Mtx& operator=(const Mtx&);
    Mtx& operator+=(const Mtx&);
    Mtx& operator-=(const Mtx&);
    Vtr operator*(const Vtr&) const;
    double* operator[](int i) const { return ets[i]; }
    double& operator()(int i, int j) { return ets[i][j]; }

    Mtx& operator+() const;
    Mtx operator+(const Mtx&) const;
    friend Mtx operator-(const Mtx&);
    friend Mtx operator-(const Mtx&, const Mtx&);
    friend ostream& operator<<(ostream& s, const Mtx& m);
};

Mtx::Mtx(int n, int m, double** dbp) {
    nrows = n;
    ncols = m;
    ets = new double* [nrows];
    for (int i = 0; i < nrows; ++i) {
        ets[i] = new double[ncols];
        for (int j = 0; j < ncols; ++j)
            ets[i][j] = dbp[i][j];
    }
}

Mtx::Mtx(int n, int m, double a) {
    ets = new double* [nrows = n];
    ncols = m;
    for (int i = 0; i < nrows; ++i) {
        ets[i] = new double[ncols];
        for (int j = 0; j < ncols; ++j)
            ets[i][j] = a;
    }
}

Mtx::Mtx(const Mtx& mat) {
    ets = new double* [nrows = mat.nrows];
    ncols = mat.ncols;
    for (int i = 0; i < nrows; ++i) {
        ets[i] = new double [ncols];
        for (int j = 0; j < ncols; ++j)
            ets[i][j] = mat[i][j];
    }
}

inline Mtx::~Mtx() {
    for (int i = 0; i < nrows; ++i)
        delete[] ets[i];
    delete[] ets;
}

Mtx& Mtx::operator=(const Mtx& mat) {
    if (this != &mat) {
        if (nrows != mat.nrows || ncols != mat.ncols)
            error("bad matrix sizes");
        for (int i = 0; i < nrows; ++i)
            for (int j = 0; j < ncols; ++j)
                ets[i][j] = mat[i][j];
    }
    return *this;
}

Mtx& Mtx::operator+=(const Mtx& mat) {
    if (nrows != mat.nrows || ncols != mat.ncols)
        error("bak matrix sizes");
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            ets[i][j] += mat[i][j];
    return *this;
}

Mtx& Mtx::operator-=(const Mtx& mat) {
    if (nrows != mat.nrows || ncols != mat.ncols)
        error("bad matrix sizes");
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            ets[i][j] -= mat[i][j];
    return *this;
}

inline Mtx& Mtx::operator+() const {
    return *(Mtx*)(this);
}

inline Mtx operator-(const Mtx& mat) {
    return Mtx(mat.nrows, mat.ncols) - mat;
}

Mtx Mtx::operator+(const Mtx& mat) const {
    if (nrows != mat.nrows || ncols != mat.ncols)
        error("bad matrix sizes");
    Mtx sum = *this;
    sum += mat;
    return sum;
}

Mtx operator-(const Mtx& m1, const Mtx& m2) {
    if (m1.nrows != m2.nrows || m1.ncols != m2.ncols)
        error("bad matrix sizes");
    Mtx sum = m1;
    sum -= m2;
    return sum;
}

Vtr Mtx::operator*(const Vtr& v) const {
    if (ncols != v.size())
        error("matrix and vector sizes do not match");
    Vtr tm(nrows);
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            tm[i] += ets[i][j]*v[j];
    return tm;
}


ostream& operator<<(ostream& s, const Mtx& m) {
    for (int i = 0; i < m.nrows; ++i) {
        for (int j = 0; j < m.ncols; ++j)
            cout << m[i][j] << " ";
        cout << endl;
    }
    return s;
}

int main(void) {
    int k = 300;
    double** mt = new double* [k];
    for (int i = 0; i < k; ++i)
        mt[i] = new double [k];
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j)
            mt[i][j] = 2*i*j + i + 10;

    Mtx m1(k, k, mt);
    Mtx m2(k, k, 5);
    Mtx m3(k, k);
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j)
            m3[i][j] = 1/(2*i+j+5.7);

    m3 += -m1 + m2;
    m1 -= m3;

    Vtr vv(k);
    for (int i = 0; i < k; ++i)
        vv[i] = 5*i + 3;
    vv = m3*vv;

    cout << "m3 = " << endl << m3 << endl;

    return 0;
}
