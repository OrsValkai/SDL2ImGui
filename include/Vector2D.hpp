// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <stdexcept>
#include <cmath>

template <typename T>
class Vector2D {
public:
    T x{};
    T y{};
    static constexpr size_t size() {
        return 2;
    }

    constexpr Vector2D() noexcept = default;
    constexpr Vector2D(const Vector2D& other) noexcept = default;
    constexpr Vector2D(Vector2D&& other) noexcept = default;
    explicit constexpr Vector2D(const T value) noexcept : x(value), y(value) {};
    constexpr Vector2D(const T x_val, const T y_val) noexcept : x(x_val), y(y_val) {}
    constexpr Vector2D& operator=(const Vector2D& other) noexcept = default;
    constexpr Vector2D& operator=(Vector2D&& other) noexcept = default;

    constexpr const T& operator[](const size_t i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("Vector2D: Index out of range");
        }
    }

    constexpr T& operator[](const size_t i) {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("Vector2D: Index out of range");
        }
    }
    
    constexpr Vector2D<T>& operator+=(const Vector2D<T>& expr) noexcept {
        x += expr[0];
        y += expr[1];
        return *this;
    }

    constexpr Vector2D<T>& operator-=(const Vector2D<T>& expr) noexcept {
        x -= expr[0];
        y -= expr[1];
        return *this;
    }
    
    constexpr Vector2D<T>& operator*=(const T& a) noexcept {
        x *= a;
        y *= a;
        return *this;
    }
    
    constexpr Vector2D<T>& operator/=(const T& a) noexcept {
        x /= a;
        y /= a;
        return *this;
    }
    
    constexpr Vector2D<T>& operator/=(const Vector2D<T>& expr) noexcept {
        x /= expr[0];
        y /= expr[1];
        return *this;
    }

    constexpr auto sum(const Vector2D<T>& expr) noexcept {
        return expr[0] + expr[1];
    }

    constexpr auto dot(const Vector2D<T>& u, const Vector2D<T>& v) noexcept {
        return sum(u[0]*v[0], u[1] * v[1]);
    }

    constexpr auto cross(const Vector2D<T>& u, const Vector2D<T>& v) noexcept {
        return u[0] * v[1] - u[1] * v[0];
    }
    
    constexpr T norm2() const noexcept {
        return dot(*this, *this);
    }
    
    constexpr T norm() const noexcept {
        return std::sqrt(norm2());
    }
    
    constexpr const Vector2D<T>& unit() noexcept {
        *this /= norm();
        return *this;
    }
};

#endif // VECTOR_2D_H
