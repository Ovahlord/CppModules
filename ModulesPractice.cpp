#include <thread>
#include <chrono>

import TestModule;

int main()
{
    using namespace std::chrono_literals;

    Logging::MyFunc();

    // cout is transitively included via TestModule.ixx export import of <iostream>
    std::cout << "Hello World!\n";

    while (true)
    {
        std::this_thread::sleep_for(10ms);
    }
}
