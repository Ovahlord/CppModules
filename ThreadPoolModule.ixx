export module ThreadPoolModule;

import <thread>;
import <vector>;

export class ThreadPool
{
public:
    ThreadPool() { }

    template<typename F, class... Args>
    void RunOnNewThreat(F&& func, Args&&... args)
    {
        _threads.push_back(std::jthread(func, args...));
    }

private:
    std::vector<std::jthread> _threads;
};
