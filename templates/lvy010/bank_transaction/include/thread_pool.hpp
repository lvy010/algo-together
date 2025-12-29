// 线程池：固定线程数，支持 submit(lambda) 返回 std::future
#pragma once

#include <condition_variable>
#include <cstddef>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t numThreads) {
        if (numThreads == 0) {
            numThreads = 1;
        }
        try {
            for (std::size_t i = 0; i < numThreads; ++i) {
                workers.emplace_back([this]{ this->workerLoop(); });
            }
        } catch (...) {
            stop();
            throw;
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ~ThreadPool() {
        stop();
    }

    template <class F, class... Args,
              class R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    std::future<R> submit(F&& f, Args&&... args) {
        auto taskPtr = std::make_shared<std::packaged_task<R()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<R> fut = taskPtr->get_future();
        {
            std::unique_lock<std::mutex> lk(mtx);
            if (isStopping) {
                throw std::runtime_error("ThreadPool stopped");
            }
            tasks.emplace([taskPtr]{
                try { (*taskPtr)(); } catch (...) { throw; }
            });
        }
        cv.notify_one();
        return fut;
    }

    void stop() noexcept {
        {
            std::unique_lock<std::mutex> lk(mtx);
            if (isStopping) return;
            isStopping = true;
        }
        cv.notify_all();
        for (std::thread& t : workers) {
            if (t.joinable()) t.join();
        }
        workers.clear();
    }

private:
    void workerLoop() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, [this]{ return isStopping || !tasks.empty(); });
                if (isStopping && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            try {
                task();
            } catch (...) {
                // 任务异常在 future 中可见，这里不吞异常
            }
        }
    }

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool isStopping {false};
};


