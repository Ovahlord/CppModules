export module ThreadPoolModule;

import <future>;
import <queue>;
export import <thread>;
import <tuple>;
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

        _pendingTasks.push([func = std::forward<F>(func), args = std::make_tuple(std::forward<Args>(args)...)]()
        {
            std::apply(func, std::move(args));
        });
    }

    bool ProcessTasks()
    {
        size_t idleThreats = 0;
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
                    ++idleThreats;
            }
            else
                ++idleThreats;
        }

        return (idleThreats != _threads.size());
    }

private:
    std::vector<std::jthread> _threads;
    std::queue<std::function<void()>> _pendingTasks;
};
