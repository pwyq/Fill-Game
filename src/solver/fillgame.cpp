#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "solver/constraint.h"
#include "solver/dfpn.h"
#include "solver/game.h"

using std::cout;
using std::endl;

// 1024 * 1024 * 1024 = 1073741824 Bytes = 1GB
#define MEMORY_LIMIT (1073741824)

void startSolver(std::string& input, size_t time_limit) {
    Game game(input);
    // cout << game << endl;

    DFPN dfpn(game);

    Constraint constraint = Constraint(MEMORY_LIMIT, time_limit);
    constraint.signalHandler = DFPN::signalHandler;
    constraint.apply();

    dfpn.solve();
    cout << dfpn.formatResult() << endl;
}

/**
void testStackMemoryLimit() { // SIGSEGV
    // long long arr[UINTMAX_MAX] = {0};    // this will give direct error;
    long long arr[10000] = {0};
    testStackMemoryLimit();
}

void testHeapMemoryLimit() { // throw bad_alloc
    int* nmbr = new int[1024*1024*255];
}

void testTimeLimit() { // SIGXCPU
    while (true) {
        cout << "time limit test\n";
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "invalid number of arguments" << endl;
        return -1;
    }
    std::string input_sequence = argv[1];
    int time_limit = std::stoi(argv[2]);

    try {
        startSolver(input_sequence, time_limit);
        // testStackMemoryLimit();
        // testHeapMemoryLimit();
        // testTimeLimit();
    } catch (const std::bad_alloc& e) {  // if a 'new' operator failed, it will throw a bad_alloc exception
        g_timer.stop();
        cout << "? None " << g_timer.duration().count() << " " << g_counter << endl;
    }
    return 0;
}
**/
