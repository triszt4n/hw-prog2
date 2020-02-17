#include <iostream>

using namespace std;

/**
 * f(X) = X/121.65, ha X > 38,
 * f(X) = 0.475*X^4 - 0.949*X^3 + 60.75*X^2 + 6*X - 38, ha X <= 38
 */

double f(double x) {
    if (x > 38) {
        return x / 121.65;
    }
    else {
        return (((0.475*x - 0.949) *x + 60.75) *x +6) *x - 38;
    }
}

int main()
{
    double x;
    while (cin >> x) {
        cout << f(x) << endl;
    }
    return 0;
}
