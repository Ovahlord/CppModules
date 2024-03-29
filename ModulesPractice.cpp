//#include <thread> // includes must be declared before importing any module

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
    std::cout << "Let's do some shenanigans!\n";

    std::cout << NumberFive() << "\n";
    std::cout << NumberTen() << "\n";

    ThreadPool pool(5);

    int input = 0;
    std::cin >> input;

    for (int i = 0; i < input; ++i)
        pool.ScheduleNewTask(PrintNumber, i);

    std::cout << "scheduled " << input << " tasks. Processing now\n";

    while (pool.ProcessTasks())
    {
        std::this_thread::sleep_for(10ms);
    }

    std::cout << "all tasks processed.\n";
}
