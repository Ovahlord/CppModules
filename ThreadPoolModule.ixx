export module ThreadPoolModule;

import <functional>;
import <queue>;
export import <thread>;
import <vector>;

export class ThreadPool
{
public:
    ThreadPool(size_t poolSize) : _threads(poolSize)
    {
    }

    template<typename F, class... Args>
    void ScheduleNewTask(F&& func, Args&&... args)
    {
        for (auto& threat : _threads)
        {
            // Find an inactive threat and push our task into it
            if (!threat.joinable())
            {
                threat = std::jthread(func, args...);
                return;
            }
        }

        _pendingTasks.push(std::bind(func, args...));
    }

    bool ProcessTasks()
    {
        size_t idleThreads = 0;
        for (auto& threat : _threads)
        {
            if (threat.joinable())
            {
                threat.join();
                if (!_pendingTasks.empty())
                {
                    threat = std::jthread(_pendingTasks.front());
                    _pendingTasks.pop();
                }
                else
                    ++idleThreads;
            }
            else
                ++idleThreads;
        }

        return (idleThreads != _threads.size());
    }

private:
    std::vector<std::jthread> _threads;
    std::queue<std::function<void(void)>> _pendingTasks;
};
