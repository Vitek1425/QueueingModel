// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef JOINT_H
#define JOINT_H

#include <QGraphicsLineItem>
#include <QObject>
#include "ElementsSystem/elementsystem.h"

class Joint : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    Joint(ElementSystem *beginElement,  ElementSystem *endElement,
          QGraphicsItem * itemParent = 0, QObject *objectParent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void updatePosition();

    //проверка выделять ли линию, и если нужно ее выделить, то выделить
    void checkAcsentLine(ElementSystem *sender);
    void disableAcsent();
    void deleteJointWithAllElements();
    void deleteJointWithLeftElement();
    void deleteJointWithRightElement();
private:    
    void createConnections();
    void acsentLine();

    ElementSystem *m_beginElement;
    ElementSystem *m_endElement;

    QColor m_colorLine;
    QColor m_colorAcsent;
    int m_timeAcsentMsec;
    int m_widthLine;
};

#endif // JOINT_H
