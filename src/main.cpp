#include <QObject>
#include <QThread>
#include <QWidget>
#include <QtCore>
#include <chrono>
#include <thread>
#include "Simulation.hpp"
#include "WorkerThread.hpp"

// This macro disables the extra cmd window popup when in Microsoft windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    Simulation world;  // Create the frontend
    /**
     * Here I am creating new thread for the backend and making a
     * backend thread connecting the worker thread and front-end. Then
     * in the Worker class I will connect the backend, so backend will
     * talk to the front end through the worker thread.
     */
    QThread* worker_thread = new QThread;
    Worker* new_worker_obj = new Worker();
    new_worker_obj->moveToThread(worker_thread);
    // Prototype => connect(obj,signal,obj,slot)
    QObject::connect(new_worker_obj, &Worker::renderAgent, &world, &Simulation::renderAgent);
    QObject::connect(new_worker_obj, &Worker::renderTarget, &world, &Simulation::renderTarget);
    // Start the mainProcess when the worker thread is called
    QObject::connect(worker_thread, &QThread::started, new_worker_obj, &Worker::mainProcess);
    // Delete thread signals when they are finished --> Secure the future
    QObject::connect(new_worker_obj, SIGNAL(finished()), worker_thread, SLOT(quit()));
    QObject::connect(new_worker_obj, SIGNAL(finished()), new_worker_obj, SLOT(deleteLater()));
    QObject::connect(worker_thread, SIGNAL(finished()), worker_thread, SLOT(deleteLater()));
    // Finally start the thread, and by that start the backend AI
    worker_thread->start();

    SDL_Event Events;
    bool run = true;
    while (run) {
        while (SDL_PollEvent(&Events)) {
            if (Events.type == SDL_QUIT) run = false;
       }
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}
