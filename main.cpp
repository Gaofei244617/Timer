#include <iostream>
#include <string>
#include <memory>
#include "timer.h"
#include "time_count.h"

using namespace std;

void EchoFunc(std::string&& s) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "test : " << s << endl;
}

int main() 
{
    Timer t;
    std::cout << "Construct timer" << std::endl;

    t.addTask(EchoFunc, "hello world!");
    std::cout << "Add task" << std::endl;

    t.start(1000);
    std::cout << "Start timer" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(20));
    std::cout << "try to expire timer!" << std::endl;

    t.stop();
    std::cout << "Stop timer" << std::endl;

    std::cout << "*********************************************************" << std::endl;

    auto tag1 = TimeCount::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto tag2 = TimeCount::now();

    std::cout << "Second: " << TimeCount::span(tag1, tag2).getSeconds() << " s" << std::endl;
    std::cout << "MilliSecond: " << TimeCount::span(tag1, tag2).getMilliSeconds() << " ms" << std::endl;
    std::cout << "MicroSecond: " << TimeCount::span(tag1, tag2).getMicroSeconds() << " us" << std::endl;
    std::cout << "NanoSecond: " << TimeCount::span(tag1, tag2).getNanoSeconds() << " ns" << std::endl;

    return 0;
}
