// Copyright(c) 2024 Valkai-Németh Béla-Örs

#ifndef VO_TIMER_HR_H
#define VO_TIMER_HR_H

#include <chrono>

namespace vo {

    class TimerHR
    {
    public:
        TimerHR();
        void Start();
        float StartMS();
        void Mark();
        long long MarkUS();
        float MarkMS();
        long long US() const;
        float MS() const;

    private:
        std::chrono::high_resolution_clock::time_point m_start;
        std::chrono::high_resolution_clock::time_point m_mark;
    };

}

#endif // VO_TIMER_HR_H

