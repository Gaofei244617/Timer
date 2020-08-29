#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>

class Timer 
{
private:
    std::atomic<bool> stop_flag;
    std::atomic<bool> try_to_stop;
    std::function<void()> m_task;

public:
    Timer() :stop_flag(true), try_to_stop(false) {}
    Timer(const Timer& t):stop_flag(t.stop_flag.load()), try_to_stop(t.try_to_stop.load()){}
    ~Timer() { stop(); }

    template<typename F, class... Args>
    void addTask(F&& f, Args&&... args)
    {
        m_task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    void start(const int interval)
    {
        if (stop_flag == false)
        {
            return;
        }
        stop_flag = false;
        std::thread([this, interval]() {
            while (try_to_stop == false)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                std::thread(m_task).detach();
            }
            stop_flag = true;
            }).detach();
    }

    void stop()
    {
        if (stop_flag || try_to_stop) 
        {
            return;
        }

        try_to_stop = true;
        if (stop_flag == true)
        {
            try_to_stop = false;
        }
    }
};

#endif
