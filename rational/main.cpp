#include <iostream>
#include <sstream>
#include <numeric>
#include <set>
#include <map>
#include <vector>

using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int p, int q) {
        if (q == 0)
            throw invalid_argument("Invalid argument");

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
    int numerator;
    int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() * rhs.Denominator() < lhs.Denominator() * rhs.Numerator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator() + lhs.Denominator() * rhs.Numerator();
    int denominator = lhs.Denominator() * rhs.Denominator();

    return {numerator, denominator};
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator() - lhs.Denominator() * rhs.Numerator();
    int denominator = lhs.Denominator() * rhs.Denominator();

    return {numerator, denominator};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Numerator();
    int denominator = lhs.Denominator() * rhs.Denominator();

    return {numerator, denominator};
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator();
    int denominator = lhs.Denominator() * rhs.Numerator();

    if (denominator == 0)
        throw domain_error("Division by zero");

    return {numerator, denominator};
}

istream& operator>>(istream& stream, Rational& rational) {
    int numerator, denominator;

    if (stream >> numerator) {
        char dlm;
        stream >> dlm;

        if (dlm == '/' && stream >> denominator)
            rational = {numerator, denominator};
    }

    return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}

int main() {
    try {
        char operation;
        Rational a, b;
        cin >> a >> operation >> b;

        if (operation == '+')
            cout << a + b;
        else if (operation == '-')
            cout << a - b;
        else if (operation == '*')
            cout << a * b;
        else if (operation == '/')
            cout << a / b;
    }
    catch(const exception& exc) {
        cout << exc.what();
    }
}
