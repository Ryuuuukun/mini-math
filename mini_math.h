#pragma once

#include <algorithm>
#include <cmath>

template<typename T = double>
struct complex {
    T re{ 0 };
    T im{ 0 };

    complex() = default;

    complex(const T re, const T im) : re(re), im(im) {}

    complex(const T re) : complex(re, 0) {}

    complex& operator+=(complex const& other) {
        re += other.re;
        im += other.im;
        return *this;
    }

    complex& operator-=(complex const& other) {
        re -= other.re;
        im -= other.im;
        return *this;
    }

    complex& operator*=(complex const& other) {
        const double _re = re;
        const double _im = im;
        re = _re * other.re - _im * other.im;
        im = _re * other.im + _im * other.re;
        return *this;
    }

    complex& operator/=(complex const& other) {
        const double _re = re;
        const double _im = im;
        re = (_re * other.re + _im * other.im) / (other.re * other.re + other.im * other.im);
        im = (_im * other.re - _re * other.im) / (other.re * other.re + other.im * other.im);
        return *this;
    }
};

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, complex<T> const& c) {
    return stream << "(" << c.re << ", " << c.im << ")";
}

template<std::size_t dim>
struct vector {
    double* data;

    explicit vector(const double var) : data(new double[dim]) {
        std::fill_n(data, dim, var);
    }

    explicit vector() : vector(0) {}

    ~vector() {
        delete[] data;
    }

    vector& operator+=(vector const& other) {
        std::transform(data, data + dim, other.data, data + dim,
                    std::plus<double>());
        return *this;
    }

    vector& operator-=(vector const& other) {
        std::transform(data, data + dim, other.data, data + dim,
                        std::minus<double>());
        return *this;
    }
};

template<std::size_t dim>
std::ostream& operator<<(std::ostream& stream, vector<dim> const& vec) {
    stream << "[";
    for (std::size_t i = 0; i < dim; i++) {
        stream << vec[i] << (i == dim - 1 ? ", " : " ");
    }
    return stream << "]";
}
