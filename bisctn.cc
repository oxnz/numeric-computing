#include <iostream>
#include <cmath>

using std::cout;
using std::endl;


double bisctn0(double a, double b, double (*f)(double), double delta,
               double epsn) {
    double c = (a + b)*0.5;
    if (fabs(b-a)*0.5 < delta || fabs(f(c)) < epsn )
        return c;
    (f(a)*f(c) < 0) ? b = c : a = c;
    return bisctn0(a, b, f, delta, epsn);
}

const double delta = 1.0e-8;
const double epsn = 1.0e-9;

double fa(double x) {
    if (x) return 1.0/x - pow(2, x);
    else {
        cout << "division by zero occurred in function fa()." << endl;
        exit(1);
    }
}

double fb(double x) {
    return pow(2, -x) + exp(x) + 2*cos(x) - 6;
}

double fc(double x) {
    double denorm = ((2*x-9)*x+18)*x-2;
    if (denorm) return (((x+4)*x+3)*x+5)/denorm;
    else {
        cout << "division by zero occured in function fc()." << endl;
        exit(1);
    }
}

// more rubst
double bisctn1(double a, double b, double (*f)(double),
               double u,double delta, double epsn) {
    double e = (b-a)*0.5;
    double c = a + e;
    double w = f(c);

    if (fabs(e) < delta || fabs(w) < epsn) return c;
    ((u > 0 && w < 0) || (u < 0 && w > 0)) ? (b=c) : (a=c, u=w);
    return bisctn1(a, b, f, u, delta, epsn);
}

// non-recursive
double bisection(double a, double b, double (*f)(double),
                 double delta, double epsn, int maxit) {
    double u = f(a);
    double e = b - a;
    double c;

    for (int k = 1; k <= maxit; ++k) {
        e *= 0.5;
        c = a + e;
        double w = f(c);
        if (fabs(e) < delta || fabs(w) < epsn) return c;
        ((u>0 && w<0) || (u<0 && w>0)) ? (b=c) : (a=c, u=w);
    }
    return c;
}

int main() {
    double root = bisctn0(1.0e-2, 1, fa, delta, epsn);
    cout << "Approximate root of fa() by bisctn0() is: " << root << endl
         << "Fcn value at approx root (residual) is: " << fa(root) << endl;
    root = bisctn0(1, 3, fb, delta, epsn);
    cout << "Approximate root of fb() by bisctn0() is: " << root << endl
    << "Fcn value at approx root (residual) is: " << fb(root) << endl;
    root = bisctn0(0, 4, fc, delta, epsn);
    cout << "Approximate root of fc() by bisctn0() is: " << root << endl
         << "Fcn value at approx root (residual) is: " << fc(root) << endl;
    root = bisection(0, 4, fc, delta, epsn, 100);
    cout << "Approximate root of fc() by bisection() is: " << root << endl
    << "Fcn value at approx root (residual) is: " << fc(root) << endl;

    return 0;
}
