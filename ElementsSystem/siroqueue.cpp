// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "ElementsSystem/siroqueue.h"
#include "request.h"
#include <QSet>

SIROQueue::SIROQueue(QGraphicsItem *parent) : QueueSystem(parent)
{
    setNameTypeQueue("SIRO");
}

SIROQueue::~SIROQueue()
{
    while (!m_requests.isEmpty())
    {
        delete m_requests.last();
        m_requests.removeLast();
    }
}

void SIROQueue::advance(int phase)
{
    if(!phase)
        return;
    if(!m_requests.isEmpty())
        trySendRequest();
}

void SIROQueue::addRequest(Request *request, ElementSystem *sender)
{
    m_requests.push_back(request);
    setCountRequests(getCountRequests() + 1);
    update();
    emit requestGotten(sender);
}

void SIROQueue::trySendRequest()
{
    for(QSet<ElementSystem*>::iterator it = m_children.begin();
        it != m_children.end() && !m_requests.isEmpty();
        ++it)
    {
        if ((*it)->isFree())
        {
            (*it)->addRequest(m_requests.takeAt(rand() % m_children.size()), this);
            setCountRequests(getCountRequests() - 1);
            return;
        }
    }
}
