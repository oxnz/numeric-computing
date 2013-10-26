/*
 * Pn(x) = anx^n + a(n-1)x^(n-1) + ... + a1x + a0
 */

double eval(double *a, int n, double x) {
    double sum = 0;
    for (int k = n; k >= 0; --k) {
        double xpowerk = 1;
        for (int i = 1; i <= k; ++i) { // or call pow(x, k)
            xpowerk *= x;
        }
        sum += a[k]*xpowerk;
    }
    return sum;
}

double horner(double *a, int n, double x) {
    double u = a[n];
    for (int i = n-1; i >= 0; --i)
        u = u*x + a[i];
    return u;
}

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

int main(void) {
    double a[9] = {1, -8, 28, -56, 70, -56, 28, -8, 1};
    for (double x = 0.99999; x <= 1.0001; x += 1.0e-5) {
        cout.width(20);
        cout << eval(a, 8, x);
        cout.width(20);
        cout << horner(a, 8, x);
        cout.width(20);
        cout << pow(x-1, 8) << endl;
    }
    return 0;
}
    
