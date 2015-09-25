// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef SIROQUEUE_H
#define SIROQUEUE_H

#include <QList>
#include "ElementsSystem/queueSystem.h"

class SIROQueue : public QueueSystem
{
public:
    SIROQueue(QGraphicsItem *parent = 0);
    virtual ~SIROQueue();
    virtual void advance(int phase);
    virtual void addRequest(Request *request, ElementSystem *sender);
private:
    void trySendRequest();

    QList<Request*> m_requests;
};

#endif // SIROQUEUE_H
