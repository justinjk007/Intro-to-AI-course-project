#include "WorkerThread.hpp"
#include <chrono>
#include <ctime>
#include <thread>
#include <iostream>
#include "AI.hpp"

void Worker::mainProcess()
{
    /**
     * This is where the backend the backend aka AI starts life, it is
     * then connected to the front end through the worker class
     */
    std::srand(std::time(nullptr));
    Environment ai;
    // Connect signals
    connect(&ai, &Environment::renderAgent, this, &Worker::renderAgent);
    connect(&ai, &Environment::renderTarget, this, &Worker::renderTarget);
    connect(&ai, &Environment::clearScreen, this, &Worker::clearScreen);

    for (int i = 1; i < 26; i++) {  // Here i is the number of iteration, for 25 iterations
        ai.initializeEnvironment();
        ai.render();
        ai.iteration = i;
        ai.play(2);
        ai.writeToFile();
        ai.clearGlobals();
    }
}
