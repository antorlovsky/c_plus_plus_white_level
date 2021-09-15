#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() {}

    Rational(int p, int q) {
        if (q < 0) {
            p *= -1;
            q *= -1;
        }

        if (p == 0)
            q = 1;

        int divisor = gcd(p, q);

        numerator = p / divisor;
        denominator = q / divisor;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator = 0;
    int denominator = 1;
};
