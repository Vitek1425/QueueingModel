// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef DEVICE_H
#define DEVICE_H

#include "ElementsSystem/elementsystem.h"
#include "randomgenerator.h"

class QGraphicsProxyWidget;
class QProgressBar;
class Request;

class Device : public ElementSystem
{
    Q_OBJECT
public:
    Device(QGraphicsItem * parent = 0);
    virtual ~Device();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual bool isFree();

    virtual QPointF getCenterLeftInput();
    virtual QPointF getCenterRightInput();

    QSize getSize() const;
    void setSize(const QSize &size);

    virtual void addRequest(Request *request, ElementSystem *sender);
    virtual void advance(int phase);

    qreal getLeftBorderDistribution() const;
    void setLeftBorderDistribution(const qreal &leftBorder);

    qreal getRightBorderDistribution() const;
    void setRightBorderDistribution(const qreal &rightBorder);

    QString getDistributionFunction() const;
    void setDistributionFunction(const QString &distributionFunction);
private:
    void drawBackground(QPainter *painter);
    void drawName(QPainter *painter);
    void drawStatus(QPainter *painter);
    void drawInputs(QPainter *painter);
    void updateGeometryProgressBar();
    void updateCentersInputsPosition();

    void doingWork();
    int generateTimeWork();
    void trySendRequest();

    //элементы для отображения модели
    QSize m_size;
    QString m_nameStatus;

    QPointF m_centerLeftInput;
    QPointF m_centerRightInput;
    qreal m_raduisInput;

    QGraphicsProxyWidget *m_proxyBar;
    QProgressBar *m_progressBar;

    //элементы для модели
    Request *m_request;
    bool m_isFree;
    bool m_isWorkReady;
    int m_timeToEndWork;

    RandomGenerator m_generatorTime;
};

#endif // DEVICE_H
