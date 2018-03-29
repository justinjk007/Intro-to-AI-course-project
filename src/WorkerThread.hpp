#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#include <QThread>
#include "Point.hpp"

class Worker : public QThread
{
    Q_OBJECT
   public slots:
    void mainProcess();  // This is kinda like the main method
   signals:
    void renderAgent(Point<int>, int);   // update/render agent
    void renderTarget(Point<int>, int);  // ipdate/render target
    void finished();
};

#endif /* WORKERTHREAD_HPP */
