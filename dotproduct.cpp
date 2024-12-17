#include <iostream>
#include <vector>
#include <stdexcept>

class Vector {
private:
    std::vector<double> components;

public:
    // Constructors
    Vector() = default;
    Vector(std::initializer_list<double> list) : components(list) {}
    Vector(const Vector& other) = default;

    // Assignment operator
    Vector& operator=(const Vector& other) = default;

    // Getters and setters
    double at(size_t index) const {
        if (index >= components.size()) {
            throw std::out_of_range("Index out of range");
        }
        return components[index];
    }

    void set(size_t index, double value) {
        if (index >= components.size()) {
            throw std::out_of_range("Index out of range");
        }
        components[index] = value;
    }

    size_t size() const { return components.size(); }

    // Arithmetic operators
    Vector operator+(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        Vector result;
        result.components.resize(components.size());
        for (size_t k = 0; k < components.size(); ++k) {
            result.components[k] = components[k] + other.components[k];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        Vector result;
        result.components.resize(components.size());
        for (size_t k = 0; k < components.size(); ++k) {
            result.components[k] = components[k] - other.components[k];
        }
        return result;
    }

    // Compound assignment operators
    Vector& operator+=(const Vector& other) {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        for (size_t k = 0; k < components.size(); ++k) {
            components[k] += other.components[k];
        }
        return *this;
    }
    Vector& operator-=(const Vector& other) {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        for (size_t k = 0; k < components.size(); ++k) {
            components[k] -= other.components[k];
        }
        return *this;
    }

    // Multiplication operators
    Vector operator*(double scalar) const {
        Vector result;
        result.components.resize(components.size());
        for (size_t k = 0; k < components.size(); ++k) {
            result.components[k] = components[k] * scalar;
        }
        return result;
    }

    friend Vector operator*(double scalar, const Vector& vector) {
        return vector * scalar;
    }

    double dot(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        double result = 0.0;
        for (size_t k = 0; k < components.size(); ++k) {
            result += components[k] * other.components[k];
        }
        return result;
    }

    // Input and output operators
    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "[";
        for (size_t k = 0; k < vector.components.size(); ++k) {
            os << vector.components[k];
            if (k != vector.components.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vector) {
        size_t size;
        is >> size;
        vector.components.resize(size);
        for (size_t k = 0; k < size; ++k) {
            is >> vector.components[k];
        }
        return is;
    }
};

int main() {
    Vector v1{6.0, 9.0, 1.0};
    Vector v2{7.0, 8.0, 1.0};

    Vector v3 = v1 + v2;
    Vector v4 = v1 - v2;
    v1 += v2;
    v1 -= v2;

    Vector v5 = v1 * 2.0;
    Vector v6 = 3.0 * v2;
    double dotProduct = v1.dot(v2);

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;
    std::cout << "v4: " << v4 << std::endl;
    std::cout << "v5: " << v5 << std::endl;
    std::cout << "v6: " << v6 << std::endl;
    std::cout << "Dot product: " << dotProduct << std::endl;
    return 0;
}
