#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
/*
 * @paramters:
 *      mxt: max iterate loop times
 */
double newton(double xp, double(*f)(double), double(*fd)(double),
              double delta, double epsn, int mxt) {
    double v = f(xp);
    double xnew;

    for (int k = 1; k <= mxt; ++k) {
        double derv = fd(xp);
        if (!derv) {
            cout << "Division by 0 occured in newton()." << endl;
            exit(1);
        }

        xnew = xp - v/derv;
        v = f(xnew);
        if (fabs(xnew - xp) < delta || fabs(v) < epsn)
            return xnew;
        xp = xnew;
    }
    return xnew;
}

double f(double x) {
    return ((x - 5)*x + 3)*x + 7;
}

double fder(double x) {
    return (3*x - 10)*x + 3;
}

int main() {
    double root = newton(5, f, fder, 1e-8, 1e-9, 500);
    cout << "Approx root near 5 by newton method is: " << root << endl
         << "Fcn value at approximate root (residual) is: " << f(root) << endl;
    return 0;
}
                              
