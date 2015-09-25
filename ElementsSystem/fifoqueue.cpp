// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "ElementsSystem/fifoqueue.h"
#include "request.h"
#include <QSet>

FIFOQueue::FIFOQueue(QGraphicsItem *parent) : QueueSystem(parent)
{
    setNameTypeQueue("FIFO");
}

FIFOQueue::~FIFOQueue()
{
    while (!m_requests.isEmpty())
    {
        delete m_requests.dequeue();
    }
}

void FIFOQueue::advance(int phase)
{
    if(!phase)
        return;
    if(!m_requests.isEmpty())
        trySendRequest();
}

void FIFOQueue::addRequest(Request *request, ElementSystem *sender)
{
    m_requests.enqueue(request);
    setCountRequests(getCountRequests() + 1);
    update();
    emit requestGotten(sender);
}

void FIFOQueue::trySendRequest()
{
    for(QSet<ElementSystem*>::iterator it = m_children.begin();
        it != m_children.end() && !m_requests.isEmpty();
        ++it)
    {
        if ((*it)->isFree())
        {
            (*it)->addRequest(m_requests.dequeue(), this);
            setCountRequests(getCountRequests() - 1);
            return;
        }
    }
}
