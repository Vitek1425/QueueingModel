// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "joint.h"
#include <QPen>
#include <QTimer>
#include <QPainter>
#include <QGraphicsScene>

Joint::Joint(ElementSystem *beginElement, ElementSystem *endElement,
             QGraphicsItem *itemParent, QObject *objectParent):
    QObject(objectParent),
    QGraphicsLineItem(itemParent)
{
    m_beginElement = beginElement;
    m_endElement = endElement;
    m_beginElement->addChildElement(m_endElement);
    m_endElement->addParentElement(m_beginElement);    

    m_timeAcsentMsec = 200;
    m_colorAcsent = QColor(Qt::red);
    m_colorLine = QColor(Qt::black);
    m_widthLine = 4;
    setPen(QPen(m_colorLine, m_widthLine, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    createConnections();
}

void Joint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QGraphicsLineItem::paint(painter, option, widget);
}

void Joint::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    deleteJointWithAllElements();
}

void Joint::updatePosition()
{
    if (scene() == NULL)
        return;
    setLine(QLineF(m_beginElement->getCenterRightInput() + m_beginElement->pos(),
                   m_endElement->getCenterLeftInput() + m_endElement->pos()));
}

void Joint::checkAcsentLine(ElementSystem *sender)
{
    if (sender == m_beginElement)
        acsentLine();
}

void Joint::disableAcsent()
{
    setPen(QPen(m_colorLine, m_widthLine, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void Joint::deleteJointWithAllElements()
{
    m_beginElement->deleteChildElement(m_endElement);
    m_endElement->deleteParentElement(m_beginElement);
    scene()->removeItem(this);
    delete this;
}

void Joint::deleteJointWithLeftElement()
{
    m_beginElement->deleteChildElement(m_endElement);
    scene()->removeItem(this);
    delete this;
}

void Joint::deleteJointWithRightElement()
{
    m_endElement->deleteParentElement(m_beginElement);
    scene()->removeItem(this);
    delete this;
}

void Joint::createConnections()
{
    connect(m_beginElement, SIGNAL(positionChanged()), SLOT(updatePosition()));
    connect(m_endElement, SIGNAL(positionChanged()), SLOT(updatePosition()));
    connect(m_endElement, SIGNAL(requestGotten(ElementSystem*)), SLOT(checkAcsentLine(ElementSystem*)));

    connect(m_beginElement, SIGNAL(destroyed(QObject*)), SLOT(deleteJointWithRightElement()));
    connect(m_endElement, SIGNAL(destroyed(QObject*)), SLOT(deleteJointWithLeftElement()));
}

void Joint::acsentLine()
{
    setPen(QPen(m_colorAcsent, m_widthLine, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QTimer::singleShot(m_timeAcsentMsec, this, SLOT(disableAcsent()));
}
