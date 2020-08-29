#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <vector>

class Timer 
{
private:
    const int buffer_size = 128;
    std::atomic<bool> stop_flag;
    std::atomic<bool> try_to_stop;
    std::function<void()> task;
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
    std::vector<std::thread> thread_vec;
    int index;
    std::thread thr;

public:
    Timer() 
        :stop_flag(true), 
        try_to_stop(false),
        thread_vec(buffer_size),
        index(0)
    {}

    Timer(const Timer& t)
        :stop_flag(t.stop_flag.load()), 
        try_to_stop(t.try_to_stop.load()),
        thread_vec(buffer_size),
        index(0)
    {}

    ~Timer() 
    { 
        stop(); 
    }

    template<typename F, class... Args>
    void addTask(F&& f, Args&&... args)
    {
        task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    void start(const int interval)
    {
        if (stop_flag == false)
        {
            return;
        }
        stop_flag = false;
        time_point = std::chrono::high_resolution_clock::now();
        thr = std::thread([this, interval]() {
            while (try_to_stop == false)
            {
                time_point = time_point + std::chrono::milliseconds(interval);
                std::this_thread::sleep_until(time_point);
                if (thread_vec[index].joinable())
                {
                    thread_vec[index].join();
                }
                thread_vec[index] = std::thread(task);
                index++;
                if (index == buffer_size)
                {
                    index = 0;
                }
            }
            stop_flag = true;
            });
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

        if (thr.joinable())
        {
            thr.join();
        }

        for (int i = 0; i < buffer_size; i++)
        {
            if (thread_vec[i].joinable())
            {
                thread_vec[i].join();
            }
        }
    }
};

#endif
