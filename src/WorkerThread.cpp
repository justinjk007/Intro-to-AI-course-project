#include <chrono>
#include <thread>
#include "WorkerThread.hpp"
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

    ai.render();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    ai.play();
}
