#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

class Singleton {
private:
    size_t m_nrCalls{ 0 };

    Singleton() = default;

public:
    void CallMe() {
        m_nrCalls++;

        std::cout << "Glad you called " << m_nrCalls << " times!" << std::endl;
    }

    static Singleton& GetInstance() {
        static Singleton sInstance;

        return sInstance;
    }
};

class LifeTime {
public:
    LifeTime() {
        std::cout << "LifeTime() // constructor\n";
    }

    LifeTime(const LifeTime& other) : m_data(other.m_data) {
        std::cout << "LifeTime() // copy constructor\n";
    }

    LifeTime(const LifeTime&& other) noexcept : m_data(other.m_data) {
        std::cout << "LifeTime() // move constructor\n";
    }

    LifeTime& operator=(const LifeTime& other) {
        m_data = other.m_data;
        std::cout << "operator=(const LifeTime&) // copy assign\n";
        return *this;
    }

    LifeTime& operator=(const LifeTime&& other) noexcept {
        m_data = other.m_data;
        std::cout << "operator=(const LifeTime&&) // move assign\n";
        return *this;
    }

    ~LifeTime() {
        std::cout << "~LifeTime() // destructor\n";
    }

    int m_data{ 0 };
};

auto make_lifetime = [](const int value) {
    LifeTime l;
    l.m_data = value;
    return l;
};

void false_main() {
    std::array<LifeTime, 2> lifeTimes{ make_lifetime(42), make_lifetime(43) };

    std::vector<int> myVec{ 3, 1, 1, 5, -1 };

    std::sort(myVec.begin(), myVec.end(), std::greater<int>());

    std::sort(myVec.begin(), myVec.end(), [](const auto& a, const auto& b) -> bool {return a < b; });
}

