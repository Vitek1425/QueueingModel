// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QGraphicsProxyWidget>
#include <QProgressBar>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include "request.h"
#include <QStyleOptionGraphicsItem>
#include <typeinfo>
#include "ElementsSystem/device.h"

Device::Device(QGraphicsItem *parent) :
    ElementSystem(parent),
    m_size(160, 100),
    m_nameStatus("Готов к работе"),
    m_proxyBar(new QGraphicsProxyWidget(this)),
    m_progressBar(new QProgressBar),
    m_raduisInput(3),
    m_centerLeftInput(m_raduisInput + 2, m_size.height()/2),
    m_centerRightInput(m_size.width() - m_raduisInput - 2, m_size.height()/2),
    m_isFree(true),
    m_isWorkReady(false),
    m_timeToEndWork(0),
    m_request(nullptr)
{
    setNameElement("Прибор 1");
    m_proxyBar->setWidget(m_progressBar);
    m_progressBar->setValue(0);
    updateGeometryProgressBar();
}

Device::~Device()
{
    if (m_request)
        delete m_request;
}

QRectF Device::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void Device::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(getColorFrame());
    painter->setBrush(QBrush(getColorBackground()));
    painter->setPen(pen);
    drawBackground(painter);
    drawName(painter);
    drawStatus(painter);
    drawInputs(painter);
}

bool Device::isFree()
{
    return m_isFree;
}

QPointF Device::getCenterLeftInput()
{
    return m_centerLeftInput;
}

QPointF Device::getCenterRightInput()
{
    return m_centerRightInput;
}

QSize Device::getSize() const
{
    return m_size;
}

void Device::setSize(const QSize &size)
{
    prepareGeometryChange();
    m_size = size;
    updateGeometryProgressBar();
    updateCentersInputsPosition();
    update();
}

void Device::addRequest(Request *request, ElementSystem *sender)
{
    m_request = request;
    m_isFree = false;
    m_isWorkReady = false;
    m_timeToEndWork = generateTimeWork();
    m_progressBar->setMaximum(m_timeToEndWork);
    m_nameStatus = QString(tr("Идёт работа"));
    emit requestGotten(sender);
    update();
}

void Device::advance(int phase)
{
    if(!phase)
        return;
    if(!m_isFree)
    {
        if(!m_isWorkReady)
        {
            doingWork();
        }
        else
        {
            trySendRequest();
        }
    }
}

qreal Device::getLeftBorderDistribution() const
{
    return m_generatorTime.getLeftBorder();
}

void Device::setLeftBorderDistribution(const qreal &leftBorder)
{
    m_generatorTime.setLeftBorder(leftBorder);
}

qreal Device::getRightBorderDistribution() const
{
    return m_generatorTime.getRightBorder();
}

void Device::setRightBorderDistribution(const qreal &rightBorder)
{
    m_generatorTime.setRightBorder(rightBorder);
}

QString Device::getDistributionFunction() const
{
    return m_generatorTime.getDistributionFunction();
}

void Device::setDistributionFunction(const QString &distributionFunction)
{
    m_generatorTime.setDistributionFunction(distributionFunction);
}

void Device::drawBackground(QPainter *painter)
{
    painter->save();
    painter->drawRoundedRect(boundingRect(), 3, 3);
    painter->restore();
}

void Device::drawName(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, 0, m_size.width(), m_size.height() / 3),
                      getNameElement(),
                      QTextOption(Qt::AlignCenter));
    painter->restore();
}

void Device::drawStatus(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, m_size.height() / 3, m_size.width(), m_size.height() / 3),
                      m_nameStatus,
                      QTextOption(Qt::AlignCenter));
    painter->restore();
}

void Device::drawInputs(QPainter *painter)
{
    painter->save();
    painter->drawEllipse(m_centerLeftInput, m_raduisInput, m_raduisInput);
    painter->drawEllipse(m_centerRightInput, m_raduisInput, m_raduisInput);
    painter->restore();
}

void Device::updateGeometryProgressBar()
{
    int margins = 3;
    m_proxyBar->setGeometry(QRectF(margins, 70, m_size.width() - 2 * margins, 25));
}

void Device::updateCentersInputsPosition()
{
    m_centerLeftInput = QPointF(m_raduisInput + 2, m_size.height()/2);
    m_centerRightInput = QPointF(m_size.width() - m_raduisInput - 2, m_size.height()/2);
}

void Device::doingWork()
{
    if (m_timeToEndWork == 0)
    {
        m_isWorkReady = true;
        m_nameStatus = QString(tr("Ожидание места"));
        update();
        return;
    }
    --m_timeToEndWork;
    m_progressBar->setValue(m_progressBar->maximum() - m_timeToEndWork);
}

int Device::generateTimeWork()
{
    return m_generatorTime.getRandom();
}

void Device::trySendRequest()
{
    for(QSet<ElementSystem*>::iterator it = m_children.begin();
        it != m_children.end();
        ++it)
    {
        if ((*it)->isFree())
        {
            (*it)->addRequest(m_request, this);
            m_request = nullptr;
            m_isFree = true;
            m_progressBar->setValue(0);
            m_nameStatus = QString(tr("Готов к работе"));
            update();
            return;
        }
    }
}


