#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class Vtr {
    int length;
    double* ets;
public:
    Vtr(int, double*);
    Vtr(int = 0, double d = 0);
    Vtr(const Vtr&);
    ~Vtr() { delete[] ets; }

    int size() const { return length; }
    Vtr& operator=(const Vtr&);
    Vtr& operator+=(const Vtr&);
    Vtr& operator-=(const Vtr&);
    double maxnorm() const;
    double twonorm() const;
    double& operator[](int i) const { return ets[i]; }

    friend Vtr operator+(const Vtr&);
    friend Vtr operator-(const Vtr&);
    friend Vtr operator+(const Vtr&, const Vtr&);
    friend Vtr operator-(const Vtr&, const Vtr&);
    friend Vtr operator*(double, const Vtr&);
    friend Vtr operator*(const Vtr&, double);
    friend Vtr operator/(const Vtr&, double);
    friend Vtr operator*(const Vtr&, const Vtr&);
    friend double dot(const Vtr&, const Vtr&);
    friend ostream& operator<<(ostream&, const Vtr&);
};

inline void error(const char* v) {
    cout << v << ". program exited" << endl;
    exit(1);
}
