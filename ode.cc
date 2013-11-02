#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

class ode {
    double tinit;
    double ison;
    double tend;
    double (*sfn)(double t, double x);
public:
    ode(double t0, double x0, double T, (*f)(double,double))
        : tinit(t0), ison(x0), tend(T), sfn(f) {}
    double* euler(int n) const {
        double*x = new double[n+1];
        double h = (tend-tinit)/n;
        x[0] = ison;
        for (int k = 0; k < n; ++k)
            x[k+1] = x[k] + h*sfn(tinit + k*h, x[k]);
        return x;
    }
}
 
