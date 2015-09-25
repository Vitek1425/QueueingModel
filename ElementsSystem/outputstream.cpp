// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QPainter>
#include <QLCDNumber>
#include <QGraphicsProxyWidget>
#include <random>
#include <qmath.h>
#include "request.h"
#include "ElementsSystem/outputstream.h"


OutputStream::OutputStream(QGraphicsItem *parent) : ElementSystem(parent)
{
    m_size = QSize(100, 100);
    m_countRejections = 0;
    setNameElement("Исходящий поток");

    m_LCDNumer = new QLCDNumber;
    m_LCDNumer->display(m_countRejections);
    m_proxyLCDN = new QGraphicsProxyWidget(this);
    m_proxyLCDN->setWidget(m_LCDNumer);
    m_raduisInput = 3;
    updateLCDNumberGemetry();

    m_centerRightInput = QPointF(m_size.width() - m_raduisInput - 2, m_size.height() / 2);

    m_timeToNextAttempt = 0;

    m_density = 0.1;
}

QRectF OutputStream::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void OutputStream::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(getColorFrame()));
    painter->setBrush(QBrush(getColorBackground()));
    drawBackground(painter);
    drawInput(painter);
    drawName(painter);
    drawCountRejections(painter);
}

bool OutputStream::isFree()
{
    return false;
}

QPointF OutputStream::getCenterLeftInput()
{
    return QPointF(0, 0);
}

QPointF OutputStream::getCenterRightInput()
{
    return m_centerRightInput;
}

QSize OutputStream::getSize() const
{
    return m_size;
}

void OutputStream::setSize(const QSize &size)
{
    prepareGeometryChange();
    m_size = size;
    updateCenterInputPosition();
    updateLCDNumberGemetry();
    update();
}

qreal OutputStream::getDensity() const
{
    return m_density;
}

void OutputStream::setDensity(const qreal &value)
{
    m_density = value;
}

void OutputStream::advance(int phase)
{
    if(!phase)
        return;
    if (m_timeToNextAttempt == 0)
    {
        trySendRequest();
        m_timeToNextAttempt = generateTimeToNextRequest();
    }
    --m_timeToNextAttempt;
    m_LCDNumer->display(m_timeToNextAttempt);
    update();
}

void OutputStream::addRequest(Request *request, ElementSystem *sender)
{
    delete request;
}


void OutputStream::drawBackground(QPainter *painter)
{
    painter->save();
    painter->drawRoundedRect(boundingRect(), 3, 3);
    painter->restore();
}

void OutputStream::drawInput(QPainter *painter)
{
    painter->save();
    painter->drawEllipse(m_centerRightInput, m_raduisInput, m_raduisInput);
    painter->restore();
}

void OutputStream::drawName(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, 0, m_size.width(), m_size.height() / 3),
                      getNameElement(),
                      QTextOption(Qt::AlignHCenter | Qt::AlignTop));
    painter->restore();
}

void OutputStream::drawCountRejections(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, 2 * m_size.height() / 3, m_size.width(), m_size.height() / 3),
                      QString("Отказов: ") + QString::number(m_countRejections),
                      QTextOption(Qt::AlignCenter | Qt::AlignBottom));
    painter->restore();
}

void OutputStream::updateCenterInputPosition()
{
    m_centerRightInput = QPointF(m_size.width() - m_raduisInput - 2, m_size.height() / 2);
}

void OutputStream::updateLCDNumberGemetry()
{
    m_proxyLCDN->setGeometry(QRectF(2,
                                    m_size.height() / 4,
                                    m_size.width() - 4 * m_raduisInput,
                                    m_size.height()/2));
}

void OutputStream::trySendRequest()
{
    for(QSet<ElementSystem*>::iterator it = m_children.begin();
        it != m_children.end();
        ++it)
    {
        if ((*it)->isFree())
        {
            (*it)->addRequest(genRequest(), this);
            return;
        }
    }
    m_countRejections++;
}

int OutputStream::generateTimeToNextRequest()
{
    static std::default_random_engine generator;
    std::exponential_distribution<double> distribution(m_density);
    return qCeil(distribution(generator));
}

Request *OutputStream::genRequest()
{
    Request *request = new Request;
    request->setInfo(getNameElement() + QString::number(m_countRequests));
    m_countRequests++;
    return request;
}

