#include <iostream>
#include <numeric> 
class Fraction {
private:
    int numerator;
    int denominator;
   // Helper function to simplify the fraction
    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) { // denominator should be positive
            numerator = -numerator;
            denominator = -denominator;
        }
    }
public:
    // Constructors
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator have to be >0 or < 0 but not =0 ");
        }
        simplify();
    }
    // Copy constructor
    Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}
    // Assignment operator
    Fraction &operator=(const Fraction &other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;

    }
    // Getters
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    // Setters
    void setNumerator(int num) {
        numerator = num;
        simplify();
    }
    void setDenominator(int denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator have to be >0 or < 0 but not =0");
        }
        denominator = denom;
        simplify();
    }
    // Conversion to double
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }
    // Overloaded compound assignment operators
    Fraction &operator+=(const Fraction &other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }
    Fraction &operator-=(const Fraction &other) {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }
    Fraction &operator*=(const Fraction &other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }
    Fraction &operator/=(const Fraction &other) {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division cannot be done further");
        }
        numerator *= other.denominator;
        denominator *= other.numerator;
        simplify();
        return *this;
    }
    // Overloaded arithmetic operators
    friend Fraction operator+(Fraction lhs, const Fraction &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Fraction operator-(Fraction lhs, const Fraction &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend Fraction operator*(Fraction lhs, const Fraction &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend Fraction operator/(Fraction lhs, const Fraction &rhs) {
        lhs /= rhs;
        return lhs;
    }
    // Overloaded input/output operators
    friend std::ostream &operator<<(std::ostream &out, const Fraction &frac) {
        out << frac.numerator << "/" << frac.denominator;
        return out;
    }
    friend std::istream &operator>>(std::istream &in, Fraction &frac) {
        char slash;
        in >> frac.numerator >> slash >> frac.denominator;
        if (frac.denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        frac.simplify();
        return in;
    }
};
// Test the class
int main() {
    Fraction f1(2, 3), f2(4, 5);
    // Test arithmetic operators
    std::cout << "f1: " << f1 << ", f2: " << f2 << "\n";
    std::cout << "f1 + f2: " << (f1 + f2) << "\n";
    std::cout << "f1 - f2: " << (f1 - f2) << "\n";
    std::cout << "f1 * f2: " << (f1 * f2) << "\n";
    std::cout << "f1 / f2: " << (f1 / f2) << "\n";
    // Test compound assignment operators
    f1 += f2;
    std::cout << "After f1 += f2, f1: " << f1 << "\n";
    f1 -= f2;
    std::cout << "After f1 -= f2, f1: " << f1 << "\n";
    f1 *= f2;
    std::cout << "After f1 *= f2, f1: " << f1 << "\n";
    f1 /= f2;
    std::cout << "After f1 /= f2, f1: " << f1 << "\n";
    // Test conversion to double
    std::cout << "f1 as double: " << f1.toDouble() << "\n";
    // Test input operator
    Fraction f3;
    std::cout << "Enter a fraction in the form a/b: ";
    std::cin >> f3;
    std::cout << "You entered: " << f3 << "\n";
    return 0;
}
