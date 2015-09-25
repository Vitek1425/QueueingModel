// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include "ElementsSystem/elementsystem.h"
#include "ElementsSystem/device.h"
#include "ElementsSystem/inputstream.h"
#include "ElementsSystem/outputstream.h"
#include "ElementsSystem/queueSystem.h"
#include "ElementsSystem/fifoqueue.h"
#include "ElementsSystem/lifoqueue.h"
#include "ElementsSystem/siroqueue.h"
#include "joint.h"

ElementSystem::ElementSystem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_isModeAddChild(false),
    m_lineModeAddChild(nullptr)
{
    setFlags(ItemSendsGeometryChanges | QGraphicsItem::ItemIsMovable | ItemIsSelectable);
    m_colorBackground = QColor(240, 240, 240);
    m_colorFrame = QColor(160, 160, 160);
    m_colorText = QColor(Qt::black);
}

void ElementSystem::addChildElement(ElementSystem *child)
{
    m_children.insert(child);
}

void ElementSystem::addParentElement(ElementSystem *parent)
{
    m_parents.insert(parent);
}

void ElementSystem::deleteChildElement(ElementSystem *child)
{
    m_children.remove(child);
}

void ElementSystem::deleteParentElement(ElementSystem *parent)
{
    m_parents.remove(parent);
}

bool ElementSystem::isChild(ElementSystem *element)
{
    return m_children.contains(element);
}

bool ElementSystem::isParent(ElementSystem *element)
{
    return m_parents.contains(element);
}

QString ElementSystem::getNameElement() const
{
    return m_nameElement;
}

void ElementSystem::setNameElement(const QString &nameElement)
{
    m_nameElement = nameElement;
}

QColor ElementSystem::getColorBackground() const
{
    return m_colorBackground;
}

void ElementSystem::setColorBackground(const QColor &colorBackground)
{
    m_colorBackground = colorBackground;
    update();
}

QColor ElementSystem::getColorFrame() const
{
    return m_colorFrame;
}

void ElementSystem::setColorFrame(const QColor &colorFrame)
{
    m_colorFrame = colorFrame;
    update();
}

QColor ElementSystem::getColorText() const
{
    return m_colorText;
}

void ElementSystem::setColorText(const QColor &colorText)
{
    m_colorText = colorText;
    update();
}

void ElementSystem::deleteElement()
{
    scene()->removeItem(this);
    delete this;
}

QVariant ElementSystem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange){
      emit positionChanged();
    }
    return QGraphicsObject::itemChange(change, value);
}

void ElementSystem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->pos(), getCenterRightInput()).length() < 5)
    {
        //включение режима добавления свзяи
        m_isModeAddChild = true;
        m_lineModeAddChild = new QGraphicsLineItem;
        m_lineModeAddChild->setPen(QPen(Qt::black, 2, Qt::DashLine));
        scene()->addItem(m_lineModeAddChild);
        m_lineModeAddChild->setLine(QLineF(getCenterRightInput() + pos(), event->scenePos()));
        return;
    }
    QGraphicsObject::mousePressEvent(event);
}

void ElementSystem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isModeAddChild)
    {
        m_lineModeAddChild->setLine(QLineF(getCenterRightInput() + pos(), event->scenePos()));
        return;
    }
    QGraphicsObject::mouseMoveEvent(event);
}

void ElementSystem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isModeAddChild)
    {
        m_lineModeAddChild->setLine(QLineF(getCenterRightInput() + pos(), event->scenePos()));

        QList<QGraphicsItem *> items = scene()->items(event->scenePos());
        for(QList<QGraphicsItem *>::iterator it = items.begin();
            it != items.end();
            ++it)
        {
            if ((typeid(*(*it)) == typeid(Device))||
                (typeid(*(*it)) == typeid(QueueSystem))||
                (typeid(*(*it)) == typeid(InputStream))||
                (typeid(*(*it)) == typeid(FIFOQueue))||
                (typeid(*(*it)) == typeid(LIFOQueue))||
                (typeid(*(*it)) == typeid(SIROQueue)))
            {
                if (*it == this)
                    break;
                ElementSystem *child = dynamic_cast<ElementSystem *> (*it);
                if (child->isParent(this))
                    break;
                if (child->isChild(this))
                    break;
                Joint *joint = new Joint(this, child);
                scene()->addItem(joint);
                joint->updatePosition();
            }
        }

        scene()->removeItem(m_lineModeAddChild);
        delete m_lineModeAddChild;
        m_isModeAddChild = false;

        return;
    }
    QGraphicsObject::mouseReleaseEvent(event);
}

void ElementSystem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << m_children.size() << m_parents.size();
}

