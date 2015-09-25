// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

#include "ElementsSystem/elementsystem.h"

class QGraphicsProxyWidget;
class QProgressBar;
class QLabel;

class QueueSystem : public ElementSystem
{
public:
    QueueSystem(QGraphicsItem * parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual bool isFree();
    virtual QPointF getCenterLeftInput();
    virtual QPointF getCenterRightInput();

    virtual QSize getSize() const;
    virtual void setSize(const QSize &size);

    int getCountRequests() const;
    void setCountRequests(int countRequests);

    int getMaxCountRequests() const;
    void setMaxCountRequests(int maxCountRequest);

    QString getNameTypeQueue() const;
    void setNameTypeQueue(const QString &nameTypeQueue);

private:
    void drawBackground(QPainter *painter);
    void drawName(QPainter *painter);
    void drawInputs(QPainter *painter);
    void drawNameType(QPainter *painter);
    void drawCountsRequests(QPainter *painter);
    void updateCenterInputPosition();
    void updateGeometryProgressBar();

    //элементы для вида
    QGraphicsProxyWidget *m_proxyBar;
    QProgressBar *m_progressBar;
    QSize m_size;

    qreal m_raduisInput;
    QPointF m_centerLeftInput;
    QPointF m_centerRightInput;

    int m_countRequests;
    int m_maxCountRequests;

    QString m_nameTypeQueue;
};

#endif // QUEUESYSTEM_H
