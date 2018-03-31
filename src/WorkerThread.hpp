#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#include <QThread>
#include <vector>
#include "Point.hpp"

class Worker : public QThread
{
    Q_OBJECT
   public slots:
    void mainProcess();  // This is kinda like the main method
   signals:
    void renderAgent(std::vector<Point<int>>, std::vector<int>);   // update/render agent
    void renderTarget(std::vector<Point<int>>, std::vector<int>);  // update/render target
    void clearScreen();
    void finished();
};

#endif /* WORKERTHREAD_HPP */
