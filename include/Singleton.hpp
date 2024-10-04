#pragma once

#include <iostream>

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