// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include "ElementsSystem/elementsystem.h"

class InputStream : public ElementSystem
{
public:
    InputStream(QGraphicsItem * parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual bool isFree();
    virtual QPointF getCenterLeftInput();
    virtual QPointF getCenterRightInput();
    QSize getSize() const;
    void setSize(const QSize &size);

    virtual void addRequest(Request *request, ElementSystem *sender);
private:
    void drawBackground(QPainter *painter);
    void drawName(QPainter *painter);
    void drawInput(QPainter *painter);
    void drawCountReceivingElements(QPainter *painter);
    void updateCenterInputPosition();

    QSize m_size;
    QPointF m_centerLeftInput;
    qreal m_raduisInput;

    int m_countReceivingElements;
};

#endif // INPUTSTREAM_H
