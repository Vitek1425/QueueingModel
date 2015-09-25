// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include <QQueue>
#include "ElementsSystem/queueSystem.h"

class FIFOQueue : public QueueSystem
{
public:
    FIFOQueue(QGraphicsItem *parent = 0);
    virtual ~FIFOQueue();
    virtual void advance(int phase);
    virtual void addRequest(Request *request, ElementSystem *sender);
private:
    void trySendRequest();

    QQueue<Request*> m_requests;
};

#endif // FIFOQUEUE_H
