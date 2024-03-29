//#include <thread> // includes must be declared before importing any module

import <thread>;
import TestModule;
import ThreadPoolModule;

using namespace std::chrono_literals;

void PrintNumber(int number)
{
    // Everyone loves race conditions, don't they?
    std::cout << number << " printed from new threat (Id: " << std::this_thread::get_id() << ")" << std::endl;
}

int main()
{
    Logging::MyFunc();

    // cout is transitively included via TestModule.ixx export import of <iostream>
    std::cout << "Hello World!\n";

    std::cout << NumberFive() << "\n";
    std::cout << NumberTen() << "\n";

    ThreadPool pool;

    int input = 0;
    std::cin >> input;

    for (int i = 0; i < input; ++i)
        pool.RunOnNewThreat(PrintNumber, i);

}
