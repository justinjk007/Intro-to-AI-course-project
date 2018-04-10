#include "WorkerThread.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
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

    int num_of_iteration = 1; // This is how final scenarios where asked

    std::cout << "Running scenario 1\n";
    for (int i = 1; i < num_of_iteration+1; i++) {  // Here i is the number of iteration, for 25 iterations
	ai.initializeEnvironment();
        ai.render();
        ai.iteration = i;
        ai.play(1);
        ai.writeToFile();
        ai.clearGlobals();
        std::cout << "Finished " << i << "th iteration\n";
    }

    std::cout << "Running scenario 2\n";
    for (int i = 1; i < num_of_iteration+1; i++) {  // Here i is the number of iteration, for 25 iterations
        ai.initializeEnvironment();
        ai.render();
        ai.iteration = i;
        ai.play(2);
        ai.writeToFile();
        ai.clearGlobals();
        std::cout << "Finished " << i << "th iteration\n";
    }

    std::cout << "Running scenario 3\n";
    for (int i = 1; i < num_of_iteration+1; i++) {  // Here i is the number of iteration, for 25 iterations
        ai.initializeEnvironment();
        ai.render();
        ai.iteration = i;
        ai.play(3);
        ai.writeToFile();
        ai.clearGlobals();
        std::cout << "Finished " << i << "th iteration\n";
    }

    ai.processData();
}
