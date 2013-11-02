#include <iostream>
#include <cmath>

using namespace std;

class Cmpx {
private:
    double re; // real part
    double im; // image part
public:
    Cmpx(double x=0, double y=0) : re(x), im(y) {}
    // Cmpx(const Cmpx& c) { re = c.re; im = c.im; }
    // Cmpx& operator=(const Cmpx& c) { re = c.re; im = c.im; return *this; }
    Cmpx& operator+=(Cmpx);
    Cmpx& operator+=(double a) { re += a; return *this; }
    Cmpx& operator-=(Cmpx);
    Cmpx& operator++() { re++; im++; return *this; }
    Cmpx& operator++(int i) { Cmpx tmp = *this; re++; im++; return tmp; }
    friend Cmpx operator*(Cmpx, Cmpx);
    friend ostream& operator<<(ostream&, Cmpx);
    friend istream& operator>>(istream&, Cmpx&);
};

Cmpx operator+(Cmpx);
Cmpx operator-(Cmpx);
Cmpx operator+(Cmpx, Cmpx);
Cmpx operator-(Cmpx, Cmpx);

inline Cmpx operator+(Cmpx z) {
    return z;
}

inline Cmpx operator+(Cmpx a, double b) {
    return a+=b;
}

inline Cmpx operator+(double a, Cmpx b) {
    return b += a;
}

inline Cmpx operator-(Cmpx z) {
    return 0-z;
}

inline Cmpx& Cmpx::operator+=(Cmpx z) {
    re += z.re;
    im += z.im;
    return *this;
}

inline Cmpx& Cmpx::operator-=(Cmpx z) {
    re -= z.re;
    im -= z.im;
    return *this;
}

inline Cmpx operator+(Cmpx a, Cmpx b) {
    return a+=b;
}

inline Cmpx operator-(Cmpx a, Cmpx b) {
    return a-=b;
}

inline Cmpx operator*(Cmpx a, Cmpx b) {
    return Cmpx(a.re*b.re-a.im*b.im, a.re*b.im+a.im*b.re);
}

ostream& operator<<(ostream& s, Cmpx z) {
    s << "(" << z.re << ", " << z.im << ")";
    return s;
}

istream& operator>>(istream& s, Cmpx& z) {
    s >> z.re >> z.im;
    return s;
}

int main(void) {
    Cmpx a(1, 1);
    Cmpx b = a;
    Cmpx c = a + b;
    c -= b;
    cout << c << endl;
    c = -b;
    cout << -c + a*b << endl;
    c++;
    ++c;
    c++;
    cout << c << endl;
    return 0;
}
