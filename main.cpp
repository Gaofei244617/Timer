////////////////////test.cpp
#include<iostream>
#include<string>
#include<memory>
#include"timer.h"

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

    return 0;
}
