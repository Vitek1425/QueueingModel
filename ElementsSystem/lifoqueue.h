// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef LIFOQUEUE_H
#define LIFOQUEUE_H

#include <QStack>
#include "ElementsSystem/queueSystem.h"

class LIFOQueue : public QueueSystem
{
public:
    LIFOQueue(QGraphicsItem *parent = 0);
    virtual ~LIFOQueue();
    virtual void advance(int phase);
    virtual void addRequest(Request *request, ElementSystem *sender);
private:
    void trySendRequest();

    QStack<Request*> m_requests;
};

#endif // LIFOQUEUE_H
