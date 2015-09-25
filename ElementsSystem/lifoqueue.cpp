// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "ElementsSystem/lifoqueue.h"
#include "request.h"
#include <QSet>

LIFOQueue::LIFOQueue(QGraphicsItem *parent) : QueueSystem(parent)
{
    setNameTypeQueue("LIFO");
}

LIFOQueue::~LIFOQueue()
{
    while (!m_requests.isEmpty())
    {
        delete m_requests.pop();
    }
}

void LIFOQueue::advance(int phase)
{
    if(!phase)
        return;
    if(!m_requests.isEmpty())
        trySendRequest();
}

void LIFOQueue::addRequest(Request *request, ElementSystem *sender)
{
    m_requests.push_back(request);
    setCountRequests(getCountRequests() + 1);
    update();
    emit requestGotten(sender);
}

void LIFOQueue::trySendRequest()
{
    for(QSet<ElementSystem*>::iterator it = m_children.begin();
        it != m_children.end() && !m_requests.isEmpty();
        ++it)
    {
        if ((*it)->isFree())
        {
            (*it)->addRequest(m_requests.pop(), this);
            setCountRequests(getCountRequests() - 1);
            return;
        }
    }
}
