// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include "ElementsSystem/elementsystem.h"

class QGraphicsProxyWidget;
class QLCDNumber;
class Request;

class OutputStream : public ElementSystem
{
public:
    OutputStream(QGraphicsItem * parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual bool isFree();
    virtual QPointF getCenterLeftInput();
    virtual QPointF getCenterRightInput();

    QSize getSize() const;
    void setSize(const QSize &size);

    qreal getDensity() const;
    void setDensity(const qreal &value);

    virtual void advance(int phase);
    virtual void addRequest(Request *request, ElementSystem *sender);

private:
    void drawBackground(QPainter *painter);
    void drawInput(QPainter *painter);
    void drawName(QPainter *painter);
    void drawCountRejections(QPainter *painter);
    void updateCenterInputPosition();
    void updateLCDNumberGemetry();

    void trySendRequest();
    int generateTimeToNextRequest();
    Request *genRequest();

    //параметры для отображения элемента
    QSize m_size;

    QLCDNumber *m_LCDNumer;
    QGraphicsProxyWidget *m_proxyLCDN;

    qreal m_raduisInput;
    QPointF m_centerRightInput;

    //параметры для свойств модели
    int m_timeToNextAttempt;
    int m_countRequests;
    int m_countRejections;

    //плотность потока
    qreal m_density;
};

#endif // OUTPUTSTREAM_H
