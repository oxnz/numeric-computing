#include <iostream>
#include <cmath>
#include "vtr.h"
using namespace std;



Vtr::Vtr(int n, double* abd) {
    ets = new double [length = n];
    for (int i = 0; i < length; ++i)
        ets[i] = *(abd+i);
}

Vtr::Vtr(int n, double a) {
    ets = new double [length = n];
    for (int i = 0; i < length; ++i)
        ets[i] = a;
}

Vtr::Vtr(const Vtr& v) {
    ets = new double [length = v.length];
    for (int i = 0; i < length; ++i)
        ets[i] = v[i];
}

Vtr& Vtr::operator=(const Vtr& v) {
    if (this != &v) {
        if (length != v.length)
            error("bad vector sizes");
        for (int i = 0; i < length; ++i)
            ets[i] = v[i];
    }
    return *this;
}

Vtr& Vtr::operator+=(const Vtr& v) {
    if (length != v.length)
        error("bad vector sizes");
    for (int i = 0; i < length; ++i)
        ets[i] += v[i];
    return *this;
}

Vtr& Vtr::operator-=(const Vtr& v) {
    if (length != v.length)
        error("bad vector sizes");
    for (int i = 0; i < length; ++i)
        ets[i] -= v[i];
    return *this;
}

inline Vtr operator+(const Vtr& v) {
    return v;
}

inline Vtr operator-(const Vtr& v) {
    return Vtr(v.length) - v;
}

Vtr operator+(const Vtr& v1, const Vtr& v2) {
    if (v1.length != v2.length)
        error("bad vector sizes");
    Vtr sum = v1;
    sum += v2;
    return sum;
}

Vtr operator-(const Vtr& v1, const Vtr& v2) {
    if (v1.length != v2.length)
        error("bad vector sizes");
    Vtr sum = v1;
    sum -= v2;
    return sum;
}

Vtr operator*(double scalar, const Vtr& v) {
    Vtr tm(v.length);
    for (int i = 0; i < v.length; ++i)
        tm[i] = scalar*v[i];
    return tm;
}

inline Vtr operator*(const Vtr& v, double scalar) {
    return scalar*v;
}

Vtr operator*(const Vtr& v1, const Vtr& v2) {
    if (v1.length != v2.length)
        error("bad vector sizes");
    int n = v1.length;
    Vtr tm(n);
    for (int i = 0; i < n; ++i)
        tm[i] = v1[i]*v2[i];
    return tm;
}

Vtr operator/(const Vtr& v, double scalar) {
    if (!scalar)
        error("division by zero in vector-scalar division");
    
    return (1.0/scalar)*v;
}

double Vtr::twonorm() const {
    double norm = ets[0]*ets[0];
    for (int i = 0; i < length; ++i)
        norm += ets[i]*ets[i];
    return sqrt(norm);
}

double Vtr::maxnorm() const {
    double norm = fabs(ets[0]);
    for (int i = 0; i < length; ++i)
        norm = max(norm, fabs(ets[i]));
    return norm;
}

double dot(const Vtr& v1, const Vtr& v2) {
    if (v1.length != v2.length)
        error("bad vector sizes");
    double tm = v1[0]*v2[0];
    for (int i = 1; i < v1.length; ++i)
        tm += v1[i]*v2[i];
    return tm;
}

ostream& operator<<(ostream& s, const Vtr& v) {
    for (int i = 0; i < v.length; ++i) {
        s << v[i] << " ";
        if (i%10 == 9)
            s << endl;
    }
    return s;
}

void f() {
    int m = 500;
    double* v = new double[m];
    for (int i = 0; i < m; ++i)
        v[i] = i*i + 10;
    Vtr v1(m, v);
    Vtr v2(m);
    for (int i = 0; i < m; ++i)
        v2[i] = 5*i - 384;
    Vtr v3(m, 5.8);

    Vtr v4 = -v1 + 3.3*v3;
    v4 += v2;
    cout << "v4: " << v4 << endl;

    Vtr v5 = - v1*v4;
    double a = dot(v1, v5);
    cout << "dot (v1, v5) = " << a << endl;
}
