#pragma once

#include <sys/resource.h>
#include <csignal>
#include <cstdlib>
#include <functional>

class Constraint {
public:
    Constraint(size_t memory_limit, size_t time_limit);

    void apply();

    std::function<void(int)> signalHandler;

private:
    struct rlimit memory_limit;
    struct rlimit time_limit;

    void setSigStack();
};
