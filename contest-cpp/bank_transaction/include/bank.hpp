#pragma once

#include <algorithm>
#include <cstddef>
#include <mutex>
#include <stdexcept>
#include <utility>
#include <vector>

class ConcurrentBank {
public:
    explicit ConcurrentBank(std::vector<long long> initialBalances)
        : balances(std::move(initialBalances)), accountMutexes(balances.size()) {}

    std::size_t numAccounts() const noexcept { return balances.size(); }

    bool deposit(std::size_t accountIndex, long long amount) {
        if (!isValidAccount(accountIndex) || amount <= 0) return false;
        std::lock_guard<std::mutex> g(accountMutexes[accountIndex]);
        balances[accountIndex] += amount;
        return true;
    }

    bool withdraw(std::size_t accountIndex, long long amount) {
        if (!isValidAccount(accountIndex) || amount <= 0) return false;
        std::lock_guard<std::mutex> g(accountMutexes[accountIndex]);
        if (balances[accountIndex] < amount) return false;
        balances[accountIndex] -= amount;
        return true;
    }

    bool transfer(std::size_t fromIndex, std::size_t toIndex, long long amount) {
        if (amount <= 0) return false;
        if (!isValidAccount(fromIndex) || !isValidAccount(toIndex)) return false;
        if (fromIndex == toIndex) return true; // 自转账视为无操作

        std::size_t a = std::min(fromIndex, toIndex);
        std::size_t b = std::max(fromIndex, toIndex);
        std::unique_lock<std::mutex> lockA(accountMutexes[a]);
        std::unique_lock<std::mutex> lockB(accountMutexes[b]);

        if (fromIndex == a) {
            if (balances[fromIndex] < amount) return false;
            balances[fromIndex] -= amount;
            balances[toIndex] += amount;
        } else {
            if (balances[fromIndex] < amount) return false;
            balances[fromIndex] -= amount;
            balances[toIndex] += amount;
        }
        return true;
    }

    long long getBalance(std::size_t accountIndex) const {
        if (!isValidAccount(accountIndex)) throw std::out_of_range("bad account");
        std::lock_guard<std::mutex> g(accountMutexes[accountIndex]);
        return balances[accountIndex];
    }

    long long sumBalances() const {
        // 顺序加锁，避免死锁
        for (std::size_t i = 0; i < accountMutexes.size(); ++i) {
            accountMutexes[i].lock();
        }
        long long s = 0;
        for (long long v : balances) s += v;
        for (std::size_t i = accountMutexes.size(); i-- > 0;) {
            accountMutexes[i].unlock();
        }
        return s;
    }

private:
    bool isValidAccount(std::size_t accountIndex) const noexcept {
        return accountIndex < balances.size();
    }

    mutable std::vector<std::mutex> accountMutexes;
    std::vector<long long> balances;
};


