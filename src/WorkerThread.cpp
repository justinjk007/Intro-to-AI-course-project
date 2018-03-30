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
    Environment ai;
    // Connect signals
    connect(&ai, &Environment::renderAgent, this, &Worker::renderAgent);
    connect(&ai, &Environment::renderTarget, this, &Worker::renderTarget);
    connect(&ai, &Environment::clearScreen, this, &Worker::clearScreen);

    ai.render();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // ai.render2();

    ai.play();
    // FIXME: Commenting out both of these means no rendering...so the
    // problem is somewhere in the render function, after it renders
    // once it can render again ?

    // Ok so render2 function 2 works
}
