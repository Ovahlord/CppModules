#include <thread> // includes must be declared before importing any module

import TestModule;

int main()
{
    Logging::MyFunc();

    // cout is transitively included via TestModule.ixx export import of <iostream>
    std::cout << "Hello World!\n";

    std::cout << NumberFive() << "\n";
    std::cout << NumberTen() << "\n";

    while (true)
    {
        std::this_thread::sleep_for(10ms);
    }
}
