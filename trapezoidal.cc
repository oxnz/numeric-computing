#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

typedef double (*pfn)(double); // define pfn
double trapezoidal(double a, double b, pfn f, int n);
double simpson(double a, double b, pfn f, int n);

double square(double d) { return d*d; }

int main(void) {
    double result = trapezoidal(0, 5, square, 100);
    cout << "Integral using trapezoidal with n = 100 is: " << result << endl;

    result = simpson(0, 5, square, 100);
    cout << "Integral using simpson with n = 100 is: " << result << endl;

    result = trapezoidal(0, 5, sqrt, 100);
    cout << "Integral using trapezoidal with n = 100 is: " << result << endl;

    result = simpson(0, 5, sqrt, 100);
    cout << "Integral using simpson with n = 100 is: " << result << endl;
    
    return 0;
}

double trapezoidal(double a, double b, pfn f, int n) {
    double h = (b - a)/n;
    double sum = f(a)*0.5;
    for (int i = 0; i < n; ++i)
        sum += f(a + i*h);
    sum += f(b)*0.5;
    return sum*h;
}

double simpson(double a, double b, pfn f, int n) {
    double h = (b - a)/n;
    double sum = f(a)*0.5;
    for (int i = 0; i < n; ++i)
        sum += f(a + i*h);
    sum += f(b)*0.5;

    double summid = 0.0;
    for (int i = 1; i <= n; ++i)
        summid += f(a + (i-0.5)*h);

    return (sum + 2*summid)*h/3.0;
}
