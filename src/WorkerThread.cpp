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

    ai.render();
}
